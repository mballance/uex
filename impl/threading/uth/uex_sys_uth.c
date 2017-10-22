/****************************************************************************
 * uex_sys_uth.c
 ****************************************************************************/
#include "uex.h"
#include "uth.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uex_thread_t uex_thread_create(
	uex_thread_f		main_f,
	void				*ud) {
	return uth_create((uth_main_f)main_f, ud);
}

uex_thread_t uex_thread_self(void) {
	return uth_self();
}

void uex_mutex_init(uth_mutex_t *m) {
	uth_mutex_init(m);
}

void uex_mutex_lock(uex_mutex_t *m) {
	uth_mutex_lock(m);
}

void uex_mutex_unlock(uex_mutex_t *m) {
	uth_mutex_unlock(m);
}

void uex_cond_init(uex_cond_t *c) {
	uth_cond_init(c);
}

void uex_cond_wait(uex_cond_t *c, uex_mutex_t *m) {
	uth_cond_wait(c, m);
}

void uex_cond_signal(uex_cond_t *c) {
	uth_cond_signal(c);
}

void uex_yield(void) {
	uth_yield();
}

