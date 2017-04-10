#include "gtest/gtest.h"
#include "uex.h"
#include "uex_irq_services.h"
#include <stdio.h>

static int irq0_num=0, irq1_num=0;

static void irq0(void *) {
	fprintf(stdout, "irq0\n");
	irq0_num++;
}

static void irq1(void *) {
	fprintf(stdout, "irq1\n");
	irq1_num++;
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

	ASSERT_EQ(8, irq0_num);
	ASSERT_EQ(8, irq1_num);
}
