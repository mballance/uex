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

#include "uex_sys_services.h"
#include "uex_thread_services.h"

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
#include "uex_dev_services.h"

/********************************************************************
 * Memory Management
 ********************************************************************/
#include "uex_mem_services.h"



#ifdef __cplusplus
}
#endif

#endif /* INCLUDED_UEX_H */
