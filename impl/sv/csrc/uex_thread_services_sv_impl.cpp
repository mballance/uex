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
int _uex_create_thread(uex_thread_f, void *, uint32_t *, uint64_t);
int _uex_thread_join(uint32_t tid);
uint32_t _uex_alloc_sem(int unsigned init);
void _uex_free_sem(uint32_t sem_id);
int _uex_mutex_lock(uint32_t sem_id);
int _uex_mutex_unlock(uint32_t mid);
int _uex_cond_wait(uint32_t c, uint32_t m);
int _uex_cond_signal(uint32_t c, uint32_t waiters);
int _uex_yield(void);
int _uex_init(void);
uint32_t _uex_thread_self(void);
int _uex_thread_main(
		uex_thread_f	main_f,
		void 			*ud);
#ifdef __cplusplus
}
#endif



int _uex_thread_main(
		uex_thread_f	main_f,
		void 			*ud) {
	fprintf(stdout, "--> uex_thread_main main_f=%p ud=%p\n", main_f, ud);
	fflush(stdout);
	try {
		main_f(ud);
	} catch (std::runtime_error &e) {
		svAckDisabledState();
		return 1;
	}
	fprintf(stdout, "<-- uex_thread_main main_f=%p ud=%p\n", main_f, ud);
	fflush(stdout);
	return 0;
}

uex_thread_t uex_thread_create(
		uex_thread_f		main_f,
		void				*ud) {
	svSetScope(uex_svScope());
	uex_thread_t tid;

	if (_uex_create_thread(main_f, ud, &tid, 0)) {
		svAckDisabledState();
		throw std::runtime_error("uex_thread_create");
	}

	return tid;
}

uex_thread_t uex_thread_create_affinity(
		uex_thread_f		main_f,
		void				*ud,
		uex_cpu_set_t		*affinity) {
	uint64_t affinity_v = 0;
	svSetScope(uex_svScope());
	uex_thread_t tid;

	for (uint32_t i=0; i<UEX_MAX_CPUS/8 && i<8; i++) {
		uint64_t tmp = affinity->mask[i];
		tmp <<= 8*i;
		affinity_v |= tmp;
	}

	if (_uex_create_thread(main_f, ud, &tid, affinity_v)) {
		svAckDisabledState();
		throw std::runtime_error("uex_thread_create");
	}

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
	memset(m, 0, sizeof(uex_mutex_t));
}

void uex_mutex_lock(uex_mutex_t *m) {
	svSetScope(uex_svScope());
	if (!m->sem_id) {
		m->sem_id = _uex_alloc_sem(1);
		m->sem_refcnt = 1;
	}

	if (_uex_mutex_lock(m->sem_id)) {
		// TODO: throw exception
		svAckDisabledState();
		throw std::runtime_error("uex_mutex_lock");
	}
}

void uex_mutex_unlock(uex_mutex_t *m) {
	svSetScope(uex_svScope());
	if (_uex_mutex_unlock(m->sem_id)) {
		svAckDisabledState();
		throw std::runtime_error("uex_mutex_unlock");
	}

	if ((m->sem_refcnt--) == 0) {
		_uex_free_sem(m->sem_id);
		m->sem_id = 0;
	}
}

void uex_cond_init(uex_cond_t *c) {
	svSetScope(uex_svScope());
	memset(c, 0, sizeof(uex_cond_t));
}

void uex_cond_wait(uex_cond_t *c, uex_mutex_t *m) {
	svSetScope(uex_svScope());

	if (c->sem_id == 0) {
		c->sem_id = _uex_alloc_sem(0);
	}
	c->waiters++;

	if (!m->sem_id) {
		fprintf(stdout, "Error: mutex not locked\n");
	}

	if (_uex_cond_wait(c->sem_id, m->sem_id)) {
		svAckDisabledState();
		throw std::runtime_error("uex_cond_wait");
	}

	if ((c->waiters--) == 0) {
		// Free the semaphore
		_uex_free_sem(c->sem_id);
		c->sem_id = 0;
	}
}

void uex_cond_signal(uex_cond_t *c) {
	// Only signal if someone is waiting
	if (c->sem_id > 0) {
		svSetScope(uex_svScope());
		if (_uex_cond_signal(c->sem_id, c->waiters)) {
			svAckDisabledState();
			throw std::runtime_error("uex_cond_signal");
		}
	}
}



