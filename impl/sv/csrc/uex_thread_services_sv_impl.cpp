/*
 * uex_thread_services_sv_impl.cpp
 *
 *  Created on: Jan 7, 2018
 *      Author: ballance
 */
#include "uex_thread_services.h"
#include "uex_dpi.h"
#include <stdio.h>
#include <stdexcept>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif
int _uex_create_thread(uex_thread_f, void *, uint32_t *);
int _uex_thread_join(uint32_t tid);
uint32_t _uex_mutex_init(void);
int _uex_mutex_lock(uint32_t mid);
int _uex_mutex_unlock(uint32_t mid);
uint32_t _uex_cond_init(void);
int _uex_cond_wait(uint32_t c, uint32_t m);
int _uex_cond_signal(uint32_t c);
int _uex_yield(void);
int _uex_init(void);
uint32_t _uex_thread_self(void);

#ifdef __cplusplus
}
#endif


int _uex_thread_main(
		uex_thread_f	main_f,
		void 			*ud);

int _uex_thread_main(
		uex_thread_f	main_f,
		void 			*ud) {
	try {
		fprintf(stdout, "--> main %p\n", ud);
		main_f(ud);
		fprintf(stdout, "<-- main %p\n", ud);
	} catch (std::runtime_error &e) {
		svAckDisabledState();
		return 1;
	}
	return 0;
}

uex_thread_t uex_thread_create(
		uex_thread_f		main_f,
		void				*ud) {
	svSetScope(uex_svScope());
	uex_thread_t tid;

	fprintf(stdout, "--> create %p\n", ud);
	if (_uex_create_thread(main_f, ud, &tid)) {
		svAckDisabledState();
		throw std::runtime_error("uex_thread_create");
	}
	fprintf(stdout, "<-- create %p\n", ud);

	return tid;
}

int uex_thread_join(uex_thread_t t) {
	if (_uex_thread_join(t)) {
		svAckDisabledState();
		throw std::runtime_error("uex_thread_join");
	}
	return 0;
}

void uex_yield(void) {
	svSetScope(uex_svScope());
	if (_uex_yield()) {
		// TODO: throw exception
		svAckDisabledState();
		throw std::runtime_error("uex_yield");
	}
}

uex_thread_t uex_thread_self(void) {
	svSetScope(uex_svScope());
	return _uex_thread_self();
}

void uex_mutex_init(uex_mutex_t *m) {
	svSetScope(uex_svScope());
	*m = _uex_mutex_init();
}

void uex_mutex_lock(uex_mutex_t *m) {
	svSetScope(uex_svScope());
	if (_uex_mutex_lock(*m)) {
		// TODO: throw exception
		svAckDisabledState();
		throw std::runtime_error("uex_mutex_lock");
	}
}

void uex_mutex_unlock(uex_mutex_t *m) {
	svSetScope(uex_svScope());
	if (_uex_mutex_unlock(*m)) {
		svAckDisabledState();
		throw std::runtime_error("uex_mutex_unlock");
	}
}

void uex_cond_init(uex_cond_t *c) {
	svSetScope(uex_svScope());
	*c = _uex_cond_init();
}

void uex_cond_wait(uex_cond_t *c, uex_mutex_t *m) {
	svSetScope(uex_svScope());
	if (_uex_cond_wait(*c, *m)) {
		svAckDisabledState();
		throw std::runtime_error("uex_cond_wait");
	}
}

void uex_cond_signal(uex_cond_t *c) {
	svSetScope(uex_svScope());
	if (_uex_cond_signal(*c)) {
		svAckDisabledState();
		throw std::runtime_error("uex_cond_signal");
	}
}



