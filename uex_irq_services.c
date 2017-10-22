/****************************************************************************
 * uex_irq_services.c
 ****************************************************************************/
#include "uex_irq_services.h"
#include "uex_msg_services.h"
#include "uex.h"
#include "uex_config.h"

typedef struct uex_irq_handler_s {
	uex_irq_f		handler;
	void			*ud;
} uex_irq_handler_t;

uex_irq_handler_t				uex_irq_handlers[UEX_MAX_IRQ] = {0};

void uex_set_irq_handler(
		uint32_t 		irq,
		uex_irq_f		f,
		void			*ud) {

	if (irq < UEX_MAX_IRQ) {
		uex_irq_handlers[irq].handler = f;
		uex_irq_handlers[irq].ud = ud;
	} else {
		uex_kpanic("Attempting to set handler for out-of-bounds IRQ %d", irq);
	}
}

void uex_trigger_irq(uint32_t irq) {
	if (uex_irq_handlers[irq].handler) {
		uex_irq_handlers[irq].handler(uex_irq_handlers[irq].ud);
	} else {
		uex_kpanic("Triggering unhandled interrupt %d", irq);
	}
}
