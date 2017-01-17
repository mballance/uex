/****************************************************************************
 * uex_irq_services.c
 ****************************************************************************/
#include "uex_irq_services.h"
#include "uex_msg_services.h"
#include "uex.h"
#include "uex_config.h"

typedef struct uex_irq_handler_s {
	uint32_t		*id;
	uex_irq_f		handler;
	void			*ud;
} uex_irq_handler_t;

uex_irq_handler_t				uex_irq_handlers[UEX_MAX_IRQ] = {0};

int32_t uex_get_irq(uint32_t *drv_id) {
	int32_t irq = -1;
	uint32_t i;

	for (i=0; i<UEX_MAX_IRQ; i++) {
		if (uex_irq_handlers[i].id == drv_id) {
			irq = i;
			break;
		}
	}

	return irq;
}

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


void uex_set_irq_id(
		uint32_t			*id,
		uint32_t			irq) {
	if (irq < UEX_MAX_IRQ) {
		uex_irq_handlers[irq].id = id;
	} else {
		uex_kpanic("UEX_MAX_IRQ=%d uex_set_irq_id=%d", UEX_MAX_IRQ, irq);
	}
}

void uex_trigger_irq(uint32_t irq) {
	if (uex_irq_handlers[irq].handler) {
		uex_irq_handlers[irq].handler(uex_irq_handlers[irq].ud);
	} else {
		uex_kpanic("Triggering unhandled interrupt %d", irq);
	}
}
