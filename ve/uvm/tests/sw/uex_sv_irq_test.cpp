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

static uex_mutex_t			m_mutex;
static uex_cond_t			m_cond;

static void irq0(void *) {
	fprintf(stdout, "irq0\n");
	uex_mutex_lock(&m_mutex);
	uex_cond_signal(&m_cond);
	uex_mutex_unlock(&m_mutex);
}

static void irq1(void *) {
	fprintf(stdout, "irq1\n");
	uex_mutex_lock(&m_mutex);
	uex_cond_signal(&m_cond);
	uex_mutex_unlock(&m_mutex);
}

TEST(UEX,sv_irq_test) {
	fprintf(stdout, "Hello there\n");
	fflush(stdout);

	uex_sv_set_interrupt_handler(&irq_handler, 0);

	uex_cond_init(&m_cond);
	uex_mutex_init(&m_mutex);

	// First, register a couple of devices
	uex_set_irq_id((uint32_t *)0x1000, 0);
	uex_set_irq_id((uint32_t *)0x2000, 1);

	// Now, register interrupts
	uex_set_irq_handler(uex_get_irq((uint32_t *)0x1000), &irq0, 0);
	uex_set_irq_handler(uex_get_irq((uint32_t *)0x2000), &irq1, 0);

	for (int i=0; i<16; i++) {
		fprintf(stdout, "--> wait irq\n");
		uex_mutex_lock(&m_mutex);
		uex_cond_wait(&m_cond, &m_mutex);
		uex_mutex_unlock(&m_mutex);
		fprintf(stdout, "<-- wait irq\n");
	}
}
