/****************************************************************************
 * uex_sys_uth.c
 ****************************************************************************/
#include "uex_thread_services.h"
#include "uex_msg_services.h"
#include "bmk.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct thread_data_s {
	uint8_t					stk[16384];
	bmk_thread_t			thread;

	uex_thread_f			main_f;
	void					*ud;

	struct thread_data_s	*next;
} thread_data_t;

// TODO: need to mutex this
// static bmk_mutex_t		pool_mutex = bmk_MU
static thread_data_t	*thread_data_pool = 0;

static int uex_thread_tramp(void *ud) {
	thread_data_t *td = (thread_data_t *)ud;
	int ret;

	ret = td->main_f(td->ud);


	return ret;
}

uex_thread_t uex_thread_create(
	uex_thread_f		main_f,
	void				*ud) {
	thread_data_t	*td;

	if (thread_data_pool) {
		td = thread_data_pool;
		thread_data_pool = thread_data_pool->next;
	} else {
		td = (thread_data_t *)malloc(sizeof(thread_data_t));
	}
	td->main_f = main_f;
	td->ud = ud;
	td->next = 0;

	bmk_thread_init(
			&td->thread,
			td->stk,
			sizeof(td->stk),
			&uex_thread_tramp,
			td);

	return &td->thread;
}

int uex_thread_join(uex_thread_t t) {
	bmk_thread_join(t);
	return 0;
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

void uex_cond_signal_async(uex_cond_t *c) {
	bmk_cond_signal_async(c);
}

void uex_event_init(uex_event_t *e) {
	bmk_event_init(e);
}

void uex_event_wait(uex_event_t *e) {
	bmk_event_wait(e);
}

void uex_event_signal(uex_event_t *e) {
	bmk_event_signal(e);
}

void uex_yield(void) {
	bmk_thread_yield();
}

// Callback from BMK notifying that the thread is free
void bmk_thread_free(bmk_thread_t *t) {
	// TODO: must mutex
	// Free stack and thread
	t->next = thread_data_pool;
	thread_data_pool = t;
}

