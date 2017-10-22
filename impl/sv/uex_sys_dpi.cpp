/****************************************************************************
 * uex_sys_dpi.c
#include "uex.h"
 ****************************************************************************/
#include "uex.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <stdexcept>

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
int _uex_irq(uint32_t id);

// Memory Services
int _uex_iowrite8(uint8_t v, uint64_t a);
int _uex_ioread8(uint8_t *v, uint64_t a);
int _uex_iowrite16(uint16_t v, uint64_t a);
int _uex_ioread16(uint16_t *v, uint64_t a);
int _uex_iowrite32(uint32_t v, uint64_t a);
int _uex_ioread32(uint32_t *v, uint64_t a);
int _uex_iowrite64(uint64_t v, uint64_t a);
int _uex_ioread64(uint64_t *v, uint64_t a);

int _uex_thread_main(
		uex_thread_f	main_f,
		void 			*ud);


typedef void *svScope;

static svScope					m_scope = 0;
static uex_interrupt_handler	m_handler = 0;
static void						*m_handler_ud = 0;

svScope svGetScope();
svScope svSetScope(const svScope s);
void svAckDisabledState(void);
int svIsDisabledState(void);

#ifdef __cplusplus
}
#endif

int _uex_init(void) {
	m_scope = svGetScope();
	fprintf(stdout, "m_scope=%p\n", m_scope);
	fflush(stdout);
	return 1;
}

uex_thread_t uex_thread_create(
		uex_thread_f		main_f,
		void				*ud) {
	svSetScope(m_scope);
	uex_thread_t tid;

	fprintf(stdout, "--> create %p\n", ud);
	if (_uex_create_thread(main_f, ud, &tid)) {
		svAckDisabledState();
		throw std::runtime_error("uex_thread_create");
	}
	fprintf(stdout, "<-- create %p\n", ud);

	return tid;
}

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

int uex_thread_join(uex_thread_t t) {
	if (_uex_thread_join(t)) {
		svAckDisabledState();
		throw std::runtime_error("uex_thread_join");
	}
	return 0;
}

void uex_yield(void) {
	svSetScope(m_scope);
	if (_uex_yield()) {
		// TODO: throw exception
		svAckDisabledState();
		throw std::runtime_error("uex_yield");
	}
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
	if (_uex_mutex_lock(*m)) {
		// TODO: throw exception
		svAckDisabledState();
		throw std::runtime_error("uex_mutex_lock");
	}
}

void uex_mutex_unlock(uex_mutex_t *m) {
	svSetScope(m_scope);
	if (_uex_mutex_unlock(*m)) {
		svAckDisabledState();
		throw std::runtime_error("uex_mutex_unlock");
	}
}

void uex_cond_init(uex_cond_t *c) {
	svSetScope(m_scope);
	*c = _uex_cond_init();
}

void uex_cond_wait(uex_cond_t *c, uex_mutex_t *m) {
	svSetScope(m_scope);
	if (_uex_cond_wait(*c, *m)) {
		svAckDisabledState();
		throw std::runtime_error("uex_cond_wait");
	}
}

void uex_cond_signal(uex_cond_t *c) {
	svSetScope(m_scope);
	if (_uex_cond_signal(*c)) {
		svAckDisabledState();
		throw std::runtime_error("uex_cond_signal");
	}
}

// Exported DPI task
int _uex_irq(uint32_t id) {

	try {
		if (m_handler) {
			m_handler(m_handler_ud, id);
		} else {
			fprintf(stdout, "FATAL: no handler\n");
		}
	} catch (std::runtime_error &e) {
		svAckDisabledState();
		return 1;
	}

	return 0;
}

void uex_sv_set_interrupt_handler(
		uex_interrupt_handler	h,
		void					*ud) {
	m_handler = h;
	m_handler_ud = ud;
}

void *uex_malloc(uint32_t sz) {
	return malloc(sz);
}

void uex_free(void *p) {
	free(p);
}

void *uex_ioremap(void *p, uint32_t sz, uint32_t flags) {
	return p;
}

void uex_iounmap(void *p) {
	// NOP
}

void uex_iowrite8(uint8_t v, void *p) {
	uint64_t a = reinterpret_cast<uint64_t>(p);
	if (_uex_iowrite8(v, a)) {
		throw std::runtime_error("uex_iowrite8");
	}
}

uint8_t uex_ioread8(void *p) {
	uint8_t v;
	uint64_t a = reinterpret_cast<uint64_t>(p);
	svSetScope(m_scope);
	if (_uex_ioread8(&v, a)) {
		throw std::runtime_error("uex_ioread8");
	}
	return v;
}

void uex_iowrite16(uint16_t v, void *p) {
	uint64_t a = reinterpret_cast<uint64_t>(p);
	svSetScope(m_scope);
	if (_uex_iowrite16(v, a)) {
		throw std::runtime_error("uex_iowrite16");
	}
}

uint16_t uex_ioread16(void *p) {
	uint16_t v;
	uint64_t a = reinterpret_cast<uint64_t>(p);
	svSetScope(m_scope);
	if (_uex_ioread16(&v, a)) {
		throw std::runtime_error("uex_ioread16");
	}
	return v;
}

void uex_iowrite32(uint32_t v, void *p) {
	svSetScope(m_scope);
	uint64_t a = reinterpret_cast<uint64_t>(p);
	if (_uex_iowrite32(v, a)) {
		throw std::runtime_error("uex_iowrite32");
	}
}

uint32_t uex_ioread32(void *p) {
	uint32_t v;
	uint64_t a = reinterpret_cast<uint64_t>(p);
	svSetScope(m_scope);
	if (_uex_ioread32(&v, a)) {
		throw std::runtime_error("uex_ioread32");
	}
	return v;
}

void uex_iowrite64(uint64_t v, void *p) {
	uint64_t a = reinterpret_cast<uint64_t>(p);
	svSetScope(m_scope);
	if (_uex_iowrite64(v, a)) {
		throw std::runtime_error("uex_iowrite64");
	}
}

uint64_t uex_ioread64(void *p) {
	uint64_t v;
	uint64_t a = reinterpret_cast<uint64_t>(p);
	svSetScope(m_scope);
	if (_uex_ioread64(&v, a)) {
		throw std::runtime_error("uex_ioread64");
	}
	return v;
}

