/*
 * uex_sys_services.h
 *
 *  Created on: Jan 7, 2018
 *      Author: ballance
 */

#ifndef INCLUDED_UEX_SYS_SERVICES_H
#define INCLUDED_UEX_SYS_SERVICES_H
#include <stdint.h>

/********************************************************************
 * uex_init()
 *
 * Must be called once from the main thread prior to using any
 * UEX services
 ********************************************************************/
void uex_init(void);

/********************************************************************
 * uex_devtree_init()
 *
 * Initialization function provided by the platform
 ********************************************************************/
void uex_devtree_init(void);

/********************************************************************
 * uex_get_nprocs()
 *
 * Returns the number of processors available on the system.
 ********************************************************************/
uint32_t uex_get_nprocs(void);



#endif /* INCLUDED_UEX_SYS_SERVICES_H */
