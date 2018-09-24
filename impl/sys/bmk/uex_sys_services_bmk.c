/*
 * uex_sys_services_bmk.c
 *
 *  Created on: Sep 20, 2018
 *      Author: ballance
 */
#include "uex_irq_services.h"
#include "bmk.h"

static uex_irq_f 		prv_handler = 0;
static void				*prv_ud = 0;

static void uex_bmk_handler(uint32_t cause) {
	if (prv_handler) {
		prv_handler(prv_ud);
	}
}

void uex_set_irq_handler(uex_irq_f handler, void *ud) {
	prv_handler = handler;
	prv_ud = ud;

	bmk_sys_set_irq_handler(&uex_bmk_handler);
	bmk_sys_enable_interrupts(handler != 0);
}


