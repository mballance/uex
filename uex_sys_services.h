/*
 * uex_sys_services.h
 *
 *  Created on: Jan 7, 2018
 *      Author: ballance
 */

#ifndef INCLUDED_UEX_SYS_SERVICES_H
#define INCLUDED_UEX_SYS_SERVICES_H
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct uex_dev_s;


/********************************************************************
 * uex_init()
 *
 * Must be called once from the main thread prior to using any
 * UEX services
 *
 * - Initializes all devices
 * - Calls sys_init hook
 ********************************************************************/
void uex_init(struct uex_dev_s **devices, uint32_t n_devices);

/********************************************************************
 * uex_get_nprocs()
 *
 * Returns the number of processors available on the system.
 ********************************************************************/
uint32_t uex_get_nprocs(void);

/********************************************************************
 * uex_get_time_ns()
 *
 * Returns the current time in nS
 ********************************************************************/
uint64_t uex_get_time_ns(void);

#ifdef __cplusplus
}
#endif


#endif /* INCLUDED_UEX_SYS_SERVICES_H */
