/*
 * uex_sys_services_impl.h
 *
 *  Created on: Jan 7, 2018
 *      Author: ballance
 */

#ifndef IMPL_SYS_UEX_SYS_SERVICES_IMPL_H_
#define IMPL_SYS_UEX_SYS_SERVICES_IMPL_H_

/********************************************************************
 * uex_sys_init()
 *
 * Function provided by the platform that is called by UEX during
 * from the uex_init() function
 *
 * uex_sys_init must ensure that:
 * - Number of processors are known
 * - Available processors are initialized and ready to execute
 ********************************************************************/
void uex_sys_init(void);

/********************************************************************
 * uex_devtree_init()
 *
 * Sets the root device tree. Called during initialization.
 * Calling uex_devtree_init() causes all drivers to be initialized
 *
 * Note: the handle to the device array is stored, and
 * must not be freed by the caller.
 ********************************************************************/
void uex_devtree_init(uex_devtree_t *devtree);

/********************************************************************
 *
 ********************************************************************/


#endif /* IMPL_SYS_UEX_SYS_SERVICES_IMPL_H_ */
