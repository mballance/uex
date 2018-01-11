/****************************************************************************
 * uex_mem_services.h
 ****************************************************************************/
#include "uex_mem_services.h"
#include <stdint.h>

void uex_iomemset(void *p, uint8_t v, uint32_t count) {
	uint32_t i=0;
	while (i < count) {
		uex_iowrite8(v, p+i);
		i++;
	}
#ifdef UNDEFINED
	while (((p+i) % 4) && (i<count)) {
		uex_iowrite8(v, p+i);
		i++;
	}
	while (((p+i) % 4) &&
#endif
}

void uex_memcpy_toio(void *d, void *s, uint32_t count) {
	uint32_t i=0;
	uint8_t *s_p = s;
	while (i < count) {
		uex_iowrite8(s_p[i], d+i);
		i++;
	}
}

void uex_memcpy_fromio(void *d, void *s, uint32_t count) {
	uint32_t i=0;
	uint8_t *d_p = d;
	while (i < count) {
		d_p[i] = uex_ioread8(s+i);
		i++;
	}
}
