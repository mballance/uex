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
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "uex_sys_services.h"
#include "uex_thread_services.h"

/********************************************************************
 * Interrupts
 ********************************************************************/
#include "uex_irq_services.h"

/********************************************************************
 * Devices
 ********************************************************************/
#include "uex_dev_services.h"

/********************************************************************
 * Memory Management
 ********************************************************************/
#include "uex_mem_services.h"

#include "uex_msg_services.h"



#ifdef __cplusplus
}
#endif

#endif /* INCLUDED_UEX_H */
