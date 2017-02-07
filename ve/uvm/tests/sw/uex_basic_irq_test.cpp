#include "gtest/gtest.h"
#include "uex.h"
#include "uex_irq_services.h"
#include <stdio.h>

static int irq_num = 0;

static void irq_handler(void *ud) {
	fprintf(stdout, "--> irq_handler\n");
	uex_trigger_irq(irq_num);

	irq_num = ((irq_num+1) % 2);
	fprintf(stdout, "<-- irq_handler\n");
}

static void irq0(void *) {
	fprintf(stdout, "irq0\n");
}

static void irq1(void *) {
	fprintf(stdout, "irq1\n");
}

TEST(UEX,basic_irq_test) {
	fprintf(stdout, "Hello there\n");
	fflush(stdout);

	// First, register a couple of devices
	uex_set_irq_id((uint32_t *)0x1000, 0);
	uex_set_irq_id((uint32_t *)0x2000, 1);

	// Now, register interrupts
	uex_set_irq_handler(uex_get_irq((uint32_t *)0x1000), &irq0, 0);
	uex_set_irq_handler(uex_get_irq((uint32_t *)0x2000), &irq1, 0);

	for (int i=0; i<16; i++) {
		uex_trigger_irq((i%2));
	}
}
