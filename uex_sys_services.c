/*
 * uex_sys_services.c
 *
 *  Created on: Jan 7, 2018
 *      Author: ballance
 */
#include "uex_sys_services.h"
// #include "uex_sys_services_impl.h"

/********************************************************************
 * uex_init()
 *
 * Must be called once from the main thread prior to using any
 * UEX services
 ********************************************************************/
void uex_init(void) {

	// TODO: initialize any UEX-internal data structures

	// Call the system-initialization hook
//TODO:	uex_sys_init();

	// Request the platform to initialize the device tree
//TODO:	uex_devtree_init();

}





