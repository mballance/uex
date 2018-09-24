/****************************************************************************
 * uex_sys_uth.c
 ****************************************************************************/
#include "uex_thread_services.h"
#include "bmk.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stack_s {
	uint8_t				stk[4096];

	uex_thread_f		main_f;
	void				*ud;

	struct stack_s		*next;
} stack_t;

// TODO: need to mutex this
// static bmk_mutex_t		pool_mutex = bmk_MU
static stack_t			*stack_pool = 0;
static bmk_thread_t		*thread_pool = 0;

static int uex_thread_tramp(void *ud) {
	stack_t *stk = (stack_t *)ud;
	bmk_thread_t *t = bmk_thread_self();
	int ret;

	ret = stk->main_f(stk->ud);

	// TODO: must mutex
	// Free stack and thread
	stk->next = stack_pool;
	stack_pool = stk;
	t->next = thread_pool;
	thread_pool = t;

	return ret;
}

uex_thread_t uex_thread_create(
	uex_thread_f		main_f,
	void				*ud) {
	bmk_thread_t 	*t;
	stack_t			*stk;

	if (stack_pool) {
		stk = stack_pool;
		stack_pool = stack_pool->next;
	} else {
		stk = (stack_t *)malloc(sizeof(stack_t));
	}
	if (thread_pool) {
		t = thread_pool;
		thread_pool = thread_pool->next;
	} else {
		t = (bmk_thread_t *)malloc(sizeof(bmk_thread_t));
	}

	bmk_thread_init(
			t,
			stk->stk,
			4096,
			&uex_thread_tramp,
			stk);

	return t;
}

uex_thread_t uex_thread_self(void) {
	return bmk_thread_self();
}

void uex_mutex_init(uex_mutex_t *m) {
	bmk_mutex_init(m);
}

void uex_mutex_lock(uex_mutex_t *m) {
	bmk_mutex_lock(m);
}

void uex_mutex_unlock(uex_mutex_t *m) {
	bmk_mutex_unlock(m);
}

void uex_cond_init(uex_cond_t *c) {
	bmk_cond_init(c);
}

void uex_cond_wait(uex_cond_t *c, uex_mutex_t *m) {
	bmk_cond_wait(c, m);
}

void uex_cond_signal(uex_cond_t *c) {
	bmk_cond_signal(c);
}

void uex_yield(void) {
	bmk_thread_yield();
}

