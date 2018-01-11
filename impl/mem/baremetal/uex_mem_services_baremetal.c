/****************************************************************************
 * uex_mem_baremetal.c
 ****************************************************************************/
#include "uex_mem_services.h"

/**
 * uex_malloc()
 *
 * Allocates a block of memory from the default memory region.
 */
void *uex_malloc(uint32_t sz) {
	return 0; // TODO:
}

/**
 * uex_free()
 *
 * Frees a block of memory previously allocated with uex_malloc()
 */
void uex_free(void *p) {

}

/**
 * uex_ioremap()
 *
 * Creates a mapping for an I/O address range. In the simplest case,
 * this will be a NOP and returns the address
 */
void *uex_ioremap(void *p, uint32_t sz, uint32_t flags) {
	return p;
}

/**
 * uex_iounmap()
 *
 * Unmaps a previous I/O address mapping. May be
 */
void uex_iounmap(void *p) {

}

/**
 * uex_iowrite8()
 */
void uex_iowrite8(uint8_t v, void *p) {
	*((volatile uint8_t *)p) = v;
}

/**
 * uex_iowrite16()
 */
void uex_iowrite16(uint16_t v, void *p) {
	*((volatile uint16_t *)p) = v;
}

/**
 * uex_iowrite32()
 */
void uex_iowrite32(uint32_t v, void *p) {
	*((volatile uint32_t *)p) = v;
}

/**
 * uex_iowrite64()
 */
void uex_iowrite64(uint64_t v, void *p) {
	*((volatile uint64_t *)p) = v;
}

/**
 * uex_ioread8()
 */
uint8_t uex_ioread8(void *p) {
	return *((volatile uint8_t *)p);
}

/**
 * uex_ioread16()
 */
uint16_t uex_ioread16(void *p) {
	return *((volatile uint16_t *)p);
}

/**
 * uex_ioread32()
 */
uint32_t uex_ioread32(void *p) {
	return *((volatile uint32_t *)p);
}

/**
 * uex_ioread64()
 */
uint64_t uex_ioread64(void *p) {
	return *((volatile uint64_t *)p);
}

#ifdef UNDEFINED
/**
 * uex_iomemset()
 */
void uex_iomemset(void *p, uint8_t v, uint32_t count) {
	// TODO:
}

/**
 * uex_memcpy_toio()
 */
void uex_memcpy_toio(void *d, void *s, uint32_t count) {
	// TODO:
}

/**
 * uex_memcpy_fromio()
 */
void uex_memcpy_fromio(void *d, void *s, uint32_t count) {
	// TODO:
}

/**
 * Allocates a block of physical memory. A mapping must be
 * created using uex_ioremap in order to access this memory
 */
void *uex_ioalloc(
		uint32_t 	sz,
		uint32_t	align,
		uint32_t	flags) {
	// TODO:
	return 0;
}

void uex_iofree(void *p) {
	// TODO:
}
#endif // UNDEFINED

