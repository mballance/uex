/****************************************************************************
 * uex.h
 ****************************************************************************/
#ifndef INCLUDED_UEX_H
#define INCLUDED_UEX_H
/**
 * Defines:
 * - uex_thread_t
 * - uex_cond_t
 * - uex_mutex_t
 */
#include "uex_sys.h"
#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************
 * uex_init()
 *
 * Called once prior to invoking the root thread
 ********************************************************************/
void uex_init(void);

/********************************************************************
 * Threads
 ********************************************************************/
typedef int (*uex_thread_f)(void *);

uex_thread_t uex_thread_create(
		uex_thread_f		main_f,
		void				*ud);

int uex_thread_join(uex_thread_t t);

void uex_yield(void);

uex_thread_t uex_thread_self(void);

void uex_mutex_init(uex_mutex_t *m);

void uex_mutex_lock(uex_mutex_t *m);

void uex_mutex_unlock(uex_mutex_t *m);

void uex_cond_init(uex_cond_t *c);

void uex_cond_wait(uex_cond_t *c, uex_mutex_t *m);

void uex_cond_signal(uex_cond_t *c);

/********************************************************************
 * Interrupts
 ********************************************************************/

typedef void (*uex_irq_f)(void *);

/**
 * uex_set_irq_handler()
 *
 * Sets a callback for the specified interrupt
 */
void uex_set_irq_handler(
		uint32_t 		irq,
		uex_irq_f		f,
		void			*ud);

/********************************************************************
 * Devices
 ********************************************************************/

typedef enum {
	UEX_DEV_CHAR,
	UEX_DEV_BLOCK,
	UEX_DEV_NONE
} uex_dev_type_e;

struct uex_dev_s;

typedef void (*uex_dev_init_f)(uex_dev_s *dev, void *addr);

typedef struct uex_dev_api_s {
	int (*write)(uex_dev_s *dev, void *data, size_t sz, int flags);
	int (*read)(uex_dev_s *dev, void *data, size_t sz, int flags);
	int (*ioctl)(uex_dev_s *dev, uint32_t cmd, void *arg);
} uex_dev_api_t;

typedef struct uex_dev_s {
	// String name for the device
	const char			*name;

	uex_dev_type_e		type;

	// Physical base address of the device
	void				*addr;

	// Driver data (often staticaly allocated)
	void				*data;

	// Initialization function for the device
	uex_dev_init_f		init;

	// List of interrupt numbers associated with the device
	uint16_t			irqs[4];
	uint32_t			n_irqs;

	uex_dev_api_t		api;

} uex_dev_t;

typedef struct uex_devtree_s {
	const char					*name;
	struct uex_devtree_s		*parent;
	struct uex_devtree_s		*sibling;
	struct uex_devtree_s		*next;
	uex_dev_t					devices[];
} uex_devtree_t;

const uex_dev_t *uex_find_device(void *addr);

const uex_dev_t *udx_find_device_by_name(const char *name);

uex_devtree_t *uex_get_devtree();

/********************************************************************
 * Memory Management
 ********************************************************************/

/**
 * uex_malloc()
 *
 * Allocates a block of memory from the default memory region.
 */
void *uex_malloc(uint32_t sz);

/**
 * uex_free()
 *
 * Frees a block of memory previously allocated with uex_malloc()
 */
void uex_free(void *p);

/**
 * uex_ioremap()
 *
 * Creates a mapping for an I/O address range. In the simplest case,
 * this will be a NOP and returns the address
 */
void *uex_ioremap(void *p, uint32_t sz, uint32_t flags);

/**
 * uex_iounmap()
 *
 * Unmaps a previous I/O address mapping. In the simplest case,
 * this will be a NOP
 */
void uex_iounmap(void *p);

/**
 * uex_iowrite8()
 */
void uex_iowrite8(uint8_t v, void *p);

/**
 * uex_iowrite16()
 */
void uex_iowrite16(uint16_t v, void *p);

/**
 * uex_iowrite32()
 */
void uex_iowrite32(uint32_t v, void *p);

/**
 * uex_iowrite64()
 */
void uex_iowrite64(uint64_t v, void *p);

/**
 * uex_ioread8()
 */
uint8_t uex_ioread8(void *p);

/**
 * uex_ioread16()
 */
uint16_t uex_ioread16(void *p);

/**
 * uex_ioread32()
 */
uint32_t uex_ioread32(void *p);

/**
 * uex_ioread64()
 */
uint64_t uex_ioread64(void *p);

/**
 * uex_iomemset()
 */
void uex_iomemset(void *p, uint8_t v, uint32_t count);

/**
 * uex_memcpy_toio()
 */
void uex_memcpy_toio(void *d, void *s, uint32_t count);

/**
 * uex_memcpy_fromio()
 */
void uex_memcpy_fromio(void *d, void *s, uint32_t count);

/**
 * Allocates a block of physical memory. A mapping must be
 * created using uex_ioremap in order to access this memory
 */
void *uex_ioalloc(
		uint32_t 	sz,
		uint32_t	align,
		uint32_t	flags);

void uex_iofree(void *p);


#ifdef __cplusplus
}
#endif

#endif /* INCLUDED_UEX_H */
