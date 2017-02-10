/****************************************************************************
 * uth.c
 ****************************************************************************/
#include "uth.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define UTH_THREAD_STATUS_ACTIVE (1 << 0)
#define UTH_THREAD_STATUS_INIT   (1 << 1)

typedef struct uth_thread_block_s {
	uth_thread_t				threads[UTH_THREAD_BLOCK_SZ];
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

#define UTH_THREAD_STATUS_ACTIVE (1 << 0)
#define UTH_THREAD_STATUS_INIT   (1 << 1)



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

		// Remove this from the active list
		prv_active_list = next->next;

		// Set the next thread as the active one
		prv_active_thread = next;

		fprintf(stdout, "active=%p\n", active);
		fprintf(stdout, "next=%p\n", next);
		fflush(stdout);
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
  if (!t->stack_base) {
    t->stack_sz = UTH_STACK_SZ;
    t->stack_base = (uint32_t *)malloc(sizeof(uint8_t)*UTH_STACK_SZ);
  }
  memset(t->stack_base, 0, sizeof(uint8_t)*t->stack_sz);

  // Add the new thread to the active-threads list
  t->next = prv_active_list;
  prv_active_list = t;
}
