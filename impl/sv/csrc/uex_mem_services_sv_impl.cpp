/*
 * uex_mem_services_sv_impl.c
 *
 *  Created on: Jan 7, 2018
 *      Author: ballance
 */
#include "uex_mem_services.h"
#include "uex_dpi.h"
#include <stdio.h>
#include <stdexcept>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif
// Memory Services
int _uex_iowrite8(uint8_t v, uint64_t a);
int _uex_ioread8(uint8_t *v, uint64_t a);
int _uex_iowrite16(uint16_t v, uint64_t a);
int _uex_ioread16(uint16_t *v, uint64_t a);
int _uex_iowrite32(uint32_t v, uint64_t a);
int _uex_ioread32(uint32_t *v, uint64_t a);
int _uex_iowrite64(uint64_t v, uint64_t a);
int _uex_ioread64(uint64_t *v, uint64_t a);

#ifdef __cplusplus
}
#endif


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
	svSetScope(uex_svScope());
	if (_uex_iowrite8(v, a)) {
		throw std::runtime_error("uex_iowrite8");
	}
}

uint8_t uex_ioread8(void *p) {
	uint8_t v;
	uint64_t a = reinterpret_cast<uint64_t>(p);
	svSetScope(uex_svScope());
	if (_uex_ioread8(&v, a)) {
		throw std::runtime_error("uex_ioread8");
	}
	return v;
}

void uex_iowrite16(uint16_t v, void *p) {
	uint64_t a = reinterpret_cast<uint64_t>(p);
	svSetScope(uex_svScope());
	if (_uex_iowrite16(v, a)) {
		throw std::runtime_error("uex_iowrite16");
	}
}

uint16_t uex_ioread16(void *p) {
	uint16_t v;
	uint64_t a = reinterpret_cast<uint64_t>(p);
	svSetScope(uex_svScope());
	if (_uex_ioread16(&v, a)) {
		throw std::runtime_error("uex_ioread16");
	}
	return v;
}

void uex_iowrite32(uint32_t v, void *p) {
	svSetScope(uex_svScope());
	uint64_t a = reinterpret_cast<uint64_t>(p);
	if (_uex_iowrite32(v, a)) {
		throw std::runtime_error("uex_iowrite32");
	}
}

uint32_t uex_ioread32(void *p) {
	uint32_t v;
	uint64_t a = reinterpret_cast<uint64_t>(p);
	svSetScope(uex_svScope());
	if (_uex_ioread32(&v, a)) {
		throw std::runtime_error("uex_ioread32");
	}
	return v;
}

void uex_iowrite64(uint64_t v, void *p) {
	uint64_t a = reinterpret_cast<uint64_t>(p);
	svSetScope(uex_svScope());
	if (_uex_iowrite64(v, a)) {
		throw std::runtime_error("uex_iowrite64");
	}
}

uint64_t uex_ioread64(void *p) {
	uint64_t v;
	uint64_t a = reinterpret_cast<uint64_t>(p);
	svSetScope(uex_svScope());
	if (_uex_ioread64(&v, a)) {
		throw std::runtime_error("uex_ioread64");
	}
	return v;
}



