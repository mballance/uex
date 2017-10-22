
#include "uex.h"

typedef struct uex_device_tree_s {
	uex_device_t		*devices;
	uint32_t			n_devices;
} uex_device_tree_t;

static uex_device_tree_t		devtree = {0, 0};


void uex_set_devtree(
		struct uex_device_s	*devices,
		uint32_t			n_devices) {
	devtree.devices = devices;
	devtree.n_devices = n_devices;
}

const uex_device_t *uex_find_device(void *base) {
	uint32_t i;

	for (i=0; i<devtree.n_devices; i++) {
		if (devtree.devices[i].addr == base) {
			return &devtree.devices[i];
		}
	}

	return 0;
}
