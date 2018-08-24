
#include <sys/types.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


struct uex_device_s;

typedef enum {
	UEX_DEV_CHAR,
	UEX_DEV_BLOCK,
	UEX_DEV_NONE
} uex_dev_type_e;

struct uex_dev_s;

/**
 * Initialization function provided by a device
 */
typedef void (*uex_dev_init_f)(struct uex_dev_s *dev);

/**
 * Device interrupt function
 */
typedef void (*uex_dev_irq_f)(struct uex_dev_s *dev);

/**
 * Defines
 */
typedef struct uex_dev_api_s {
	int (*write)(struct uex_dev_s *dev, void *data, size_t sz, int flags);
	int (*read)(struct uex_dev_s *dev, void *data, size_t sz, int flags);
	int (*ioctl)(struct uex_dev_s *dev, uint32_t cmd, void *arg);
} uex_dev_api_t;

typedef struct uex_dev_s {
	// String name for the device
	const char			*name;

	// Physical base address of the device
	void				*addr;

	uex_dev_type_e		type;

	// Initialization function for the device
	uex_dev_init_f		init;

	// Interrupt function for the device
	uex_dev_irq_f		irq;

	uex_dev_api_t		api;

} uex_dev_t;

#define UEX_DEV_STATIC_INIT(__name, __base_addr, __init) { \
 .name = __name, \
 .addr = (void *)__base_addr, \
 .init = &(__init), \
 .irq = 0, \
}

//typedef struct uex_devtree_s {
//	const char					*name;
//	struct uex_devtree_s		*parent;
//	struct uex_devtree_s		*sibling;
//	struct uex_devtree_s		*next;
//	uex_dev_t					devices[];
//} uex_devtree_t;
//
//
//void uex_init_devices(uex_dev_t **devices, uint32_t n_devices);
//
uex_dev_t *uex_get_device(uint32_t devid);
//
//
//
//const uex_dev_t *uex_find_device(void *addr);
//
///**
// * Finds a device by searching through the device tree
// *
// */
//const uex_dev_t *udx_find_device_by_name(const char *name);
//
//uex_devtree_t *uex_get_devtree();
//
///**
// * Sets the root device tree. Must be called during initialization.
// *
// * Note: the handle to the device array is stored, and
// * must not be freed by the caller.
// */
//void uex_set_devtree(uex_devtree_t *devtree);
//
///**
// * Utility function to add a sibling to a device tree
// */
//void uex_devtree_add_sibling(uex_devtree_t *devtree, uex_devtree_t *sibling);
//
//void uex_devtree_add_child(uex_devtree_t *devtree, uex_devtree_t *child);


#ifdef __cplusplus
}
#endif
