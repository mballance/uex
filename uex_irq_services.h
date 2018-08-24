/****************************************************************************
 * uex_irq_services.h
 *
 * Kernel-provided functions used by platform interrupt handler
 ****************************************************************************/
#ifndef INCLUDED_UEX_IRQ_SERVICES_H
#define INCLUDED_UEX_IRQ_SERVICES_H
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Handler-function type for global interrupts
 */
typedef void (*uex_irq_f)(void *);

/**
 * Called to set an global interrupt-handler function
 */
void uex_set_irq_handler(uex_irq_f handler, void *ud);

/**
 * Calls the handler for a specific device
 */
void uex_trigger_irq(uint32_t devid);

#ifdef __cplusplus
}
#endif

#endif /* INCLUDED_UEX_IRQ_SERVICES_H */
