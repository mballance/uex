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

int _uex_thread_main(
		uex_thread_f	main_f,
		void 			*ud);

typedef void *svScope;

static svScope			m_scope = 0;

svScope svGetScope();
svScope svSetScope(const svScope s);

int _uex_init(void) {
	fprintf(stdout, "_uex_init()\n");
	fflush(stdout);
	m_scope = svGetScope();
	return 1;
}

uex_thread_t uex_thread_create(
		uex_thread_f		main_f,
		void				*ud) {
	svSetScope(m_scope);

	fprintf(stdout, "--> uex_thread_create\n");
	fflush(stdout);

	_uex_create_thread(main_f, ud);

	fprintf(stdout, "<-- uex_thread_create\n");
	fflush(stdout);
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

int uex_thread_join(uex_thread_t t) {

}

void uex_yield(void) {
	svSetScope(m_scope);
	fprintf(stdout, "--> _uex_yield()\n");
	fflush(stdout);
	_uex_yield();
	fprintf(stdout, "<-- _uex_yield()\n");
	fflush(stdout);
}

uex_thread_t uex_thread_self(void) {
	svSetScope(m_scope);
	return _uex_thread_self();
}

void uex_mutex_init(uex_mutex_t *m) {
	svSetScope(m_scope);
	*m = _uex_mutex_init();
}

void uex_mutex_lock(uex_mutex_t *m) {
	svSetScope(m_scope);
	_uex_mutex_lock(*m);
}

void uex_mutex_unlock(uex_mutex_t *m) {
	svSetScope(m_scope);
	_uex_mutex_unlock(*m);
}

void uex_cond_init(uex_cond_t *c) {
	svSetScope(m_scope);
	*c = _uex_cond_init();
}

void uex_cond_wait(uex_cond_t *c, uex_mutex_t *m) {
	svSetScope(m_scope);
	_uex_cond_wait(*c, *m);
}

void uex_cond_signal(uex_cond_t *c) {
	svSetScope(m_scope);
	_uex_cond_signal(*c);
}

