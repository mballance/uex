/****************************************************************************
 * uex_irq_services.h
 *
 * Kernel-provided functions used by platform interrupt handler
 ****************************************************************************/
#ifndef INCLUDED_UEX_IRQ_SERVICES_H
#define INCLUDED_UEX_IRQ_SERVICES_H

/**
 * Configures the device base address (id) mapping to interrupt source id
 */
void uex_set_irq_id(uint32_t *id, uint32_t irq);

/**
 * Triggers a specific interrupt
 */
void uex_trigger_irq(uint32_t irq);

#endif /* INCLUDED_UEX_IRQ_SERVICES_H */
