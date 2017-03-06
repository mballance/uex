/****************************************************************************
 * uex_sys_dpi.c
#include "uex.h"
 ****************************************************************************/
#include "uex.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

void _uex_create_thread(uex_thread_f, void *);
uint32_t _uex_mutex_init(void);
void _uex_mutex_lock(uint32_t mid);
void _uex_mutex_unlock(uint32_t mid);
uint32_t _uex_cond_init(void);
void _uex_cond_wait(uint32_t c, uint32_t m);
void _uex_cond_signal(uint32_t c);
void _uex_yield(void);
int _uex_init(void);
uint32_t _uex_thread_self(void);
int _uex_irq(void);

int _uex_thread_main(
		uex_thread_f	main_f,
		void 			*ud);

static uex_interrupt_handler	m_handler = 0;
static void						*m_handler_ud = 0;

typedef struct {
	uex_thread_f		main_f;
	void				*main_ud;
} uex_ud_t;

static void *uex_thread_trampoline(void	*ud) {
	uex_ud_t *uex_ud = (uex_ud_t *)ud;

}

/**
 * uex_thread_create()
 */
uex_thread_t uex_thread_create(
		uex_thread_f		main_f,
		void				*ud) {
	uex_thread_t	t;

	pthread_create(&t, 0);

	return t;
}


int _uex_thread_main(
		uex_thread_f	main_f,
		void 			*ud) {
	fprintf(stdout, "--> _uex_thread_main()\n");
	fflush(stdout);
	main_f(ud);
	fprintf(stdout, "<-- _uex_thread_main()\n");
	fflush(stdout);
	return 0;
}

/**
 * uex_thread_join()
 */
int uex_thread_join(uex_thread_t t) {

}

/**
 * uex_yield()
 *
 * Block calling thread to allow selection of a different thread
 */
void uex_yield(void) {
	svSetScope(m_scope);
	fprintf(stdout, "--> _uex_yield()\n");
	fflush(stdout);
	_uex_yield();
	fprintf(stdout, "<-- _uex_yield()\n");
	fflush(stdout);
}

/**
 * uex_thread_self()
 */
uex_thread_t uex_thread_self(void) {
	return pthread_self();
}

void uex_mutex_init(uex_mutex_t *m) {
	pthread_mutex_init(m, 0);
}

void uex_mutex_lock(uex_mutex_t *m) {
	pthread_mutex_lock(m);
}

void uex_mutex_unlock(uex_mutex_t *m) {
	pthread_mutex_unlock(m);
}

void uex_cond_init(uex_cond_t *c) {
	pthread_cond_init(c);
}

void uex_cond_wait(uex_cond_t *c, uex_mutex_t *m) {
	pthread_cond_wait(c, m);
}

void uex_cond_signal(uex_cond_t *c) {
	pthread_cond_signal(c);
}

// Exported DPI task
int _uex_irq(void) {
	if (m_handler) {
		m_handler(m_handler_ud);
	} else {
		fprintf(stdout, "FATAL: no handler\n");
	}

	return 0;
}

void uex_sv_set_interrupt_handler(
		uex_interrupt_handler	h,
		void					*ud) {
	m_handler = h;
	m_handler_ud = ud;
}
