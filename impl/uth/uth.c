/****************************************************************************
 * uth.c
 ****************************************************************************/
#include "uth.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define UTH_THREAD_STATUS_ACTIVE  (1 << 0)
#define UTH_THREAD_STATUS_INIT    (1 << 1)
#define UTH_THREAD_STATUS_BLOCKED (1 << 2)

typedef struct uth_thread_block_s {
	uth_thread_t				threads[UTH_THREAD_BLOCK_SZ];
	uint32_t					stacks[UTH_THREAD_BLOCK_SZ][UTH_STACK_SZ/4];
	struct uth_thread_block_s	*next;
} uth_thread_block_t;

static uth_thread_t				prv_main_thread;
static uth_thread_t				*prv_active_thread = 0;
static uth_thread_t				*prv_active_list = 0;
static uth_thread_block_t		prv_thread_block = {0};

extern void uth_swap(
	uth_thread_t		*curr,
	uth_thread_t		*next);

void uth_thread_trampoline(uth_thread_t *t) {
    t->status |= UTH_THREAD_STATUS_INIT;

    fprintf(stdout, "uth_thread_trampoline\n");
    fflush(stdout);
    fprintf(stdout, "  t=%p\n", t);
    fflush(stdout);
    fprintf(stdout, "  main_f=%p\n", t->main_f);
    fflush(stdout);
	t->main_f(t->ud);

	// The thread ended
	t->status = 0;
}


void uth_yield(void) {
	uth_thread_t		*next;

	if (!prv_active_thread) {
		// We're the main thread, and we must initialize
		memset(&prv_main_thread, 0, sizeof(uth_thread_t));
		prv_main_thread.status =
          (UTH_THREAD_STATUS_ACTIVE | UTH_THREAD_STATUS_INIT);
		prv_active_thread = &prv_main_thread;
	}

	if ((next=prv_active_list)) {
		uth_thread_t *active = prv_active_thread;
		uth_thread_t *t;

		// Remove this from the active list
		prv_active_list = next->next;

		// Set the next thread as the active one
		prv_active_thread = next;

		fprintf(stdout, "active=%p\n", active);
		fprintf(stdout, "next=%p\n", next);
		fflush(stdout);

		// Add the active thread to the end of the list,
		// provided it isn't blocked
		if (!(active->status & UTH_THREAD_STATUS_BLOCKED)) {
			if ((t=prv_active_list)) {
				while (t->next) {
					t = t->next;
				}
				t->next = active;
			} else {
				prv_active_list = active;
			}
			active->next = 0;
		}

		uth_swap(active, next);

		// Set the active thread back
		prv_active_thread = active;
	} else {
		// Just return
	}
}

uth_thread_t *uth_create(uth_main_f f, void *ud) {
  uth_thread_t *t = 0;
  uth_thread_block_t *b = &prv_thread_block;
  uint32_t bi=0;

  do {
    for (bi=0; bi<UTH_THREAD_BLOCK_SZ; bi++) {
      if (!(b->threads[bi].status & UTH_THREAD_STATUS_ACTIVE)) {
        t = &b->threads[bi];
        t->stack_base = b->stacks[bi];
        t->stack_sz = UTH_STACK_SZ;
        t->status |= UTH_THREAD_STATUS_ACTIVE;
        break;
      }
    }

    if (!t) {
      // Move to the next block
      if (!b->next) {
        uth_thread_block_t *nb = (uth_thread_block_t *)malloc(
            sizeof(uth_thread_block_t));
        memset(nb, 0, sizeof(uth_thread_block_t));
        b->next = nb;
      }

      b = b->next;
    }
  } while (!t);

  t->main_f = f;
  t->ud     = ud;
//  if (!t->stack_base) {
//    t->stack_sz = UTH_STACK_SZ;
//    t->stack_base = (uint32_t *)malloc(sizeof(uint8_t)*UTH_STACK_SZ);
//  }
  memset(t->stack_base, 0, sizeof(uint8_t)*t->stack_sz);

  // Add the new thread to the active-threads list
  t->next = prv_active_list;
  prv_active_list = t;
}

// Blocks the active thread
static void uth_thread_block() {
	prv_active_thread->status |= UTH_THREAD_STATUS_BLOCKED;

	uth_yield();

	if ((prv_active_thread->status & UTH_THREAD_STATUS_BLOCKED)) {
		fprintf(stdout, "Error: blocked thread returned\n");
	}
}

static void uth_thread_unblock(uth_thread_t *t) {
	t->status &= ~(UTH_THREAD_STATUS_BLOCKED);

	// Add this thread back to the active list
	t->next = prv_active_list;
	prv_active_list = t;

	// Allow the other thread to wake up
	uth_yield();
}

void uth_mutex_init(uth_mutex_t *m) {
	memset(m, 0, sizeof(uth_mutex_t));
}

void uth_mutex_lock(uth_mutex_t *m) {
	if (!m->owner) {
		// Just make the active thread the owner
		m->owner = prv_active_thread;
	} else {
		// Need to block ourselves
		prv_active_thread->next = m->waiters;
		m->waiters = prv_active_thread;

		uth_thread_block();
	}
}

void uth_mutex_unlock(uth_mutex_t *m) {
	if (m->waiters) {
		// Remove the head thread
		m->owner = m->waiters;
		m->waiters = m->waiters->next;

		uth_thread_unblock(m->owner);
	} else {
		m->owner = 0;
	}
}

void uth_cond_init(uth_cond_t *c) {
	memset(c, 0, sizeof(uth_cond_t));
}

void uth_cond_wait(uth_cond_t *c, uth_mutex_t *t) {
	prv_active_thread->next = c->waiters;
	c->waiters = prv_active_thread;

	uth_mutex_unlock(t);
	uth_thread_block();
	uth_mutex_lock(t);
}

void uth_cond_signal(uth_cond_t *c) {
	if (c->waiters) {
		uth_thread_t *t = c->waiters;
		c->waiters = c->waiters->next;

		uth_thread_unblock(t);
	}
}

void uth_cond_signalall(uth_cond_t *c) {
	while (c->waiters) {
		uth_thread_t *t = c->waiters;
		c->waiters = c->waiters->next;

		uth_thread_unblock(t);
	}
}

