/*
 * uex_sys_services.c
 *
 *  Created on: Jan 7, 2018
 *      Author: ballance
 */
#include "uex_sys_services.h"
#include "uex_dev_services.h"
// #include "uex_sys_services_impl.h"

static uex_dev_t **prv_devices;

uex_dev_t *uex_get_device(uint32_t devid) {
	return prv_devices[devid];
}

/********************************************************************
 * uex_init()
 *
 * Must be called once from the main thread prior to using any
 * UEX services
 ********************************************************************/
void uex_init(struct uex_dev_s **devices, uint32_t n_devices) {
	int i;
	prv_devices = devices;

	// Initialize each device
	for (i=0; i<n_devices; i++) {
		devices[i]->init(devices[i]);
	}

	// TODO: initialize any UEX-internal data structures

	// Call the system-initialization hook
//TODO:	uex_sys_init();

	// Request the platform to initialize the device tree
//TODO:	uex_devtree_init();

}





