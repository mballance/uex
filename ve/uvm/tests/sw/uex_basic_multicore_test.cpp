#include "gtest/gtest.h"
#include "uex.h"
#include <stdio.h>

static int thread1_main(void *ud) {
	for (int i=0; i<16; i++) {
		fprintf(stdout, "thread1_main %d\n", uex_thread_self());
		uex_iowrite32(i, (void *)0x00000010);
		uex_yield();
	}
	return 0;
}

static int thread2_main(void *ud) {
	for (int i=0; i<16; i++) {
		fprintf(stdout, "thread2_main %d\n", uex_thread_self());
		uex_iowrite32(i, (void *)0x00000020);
		uex_yield();
	}
	return 0;
}

TEST(UEX,basic_multicore_test) {
	uex_cpu_set_t	cpu_set_0, cpu_set_1;
	fprintf(stdout, "Hello there\n");
	fflush(stdout);

	UEX_CPU_ZERO(cpu_set_0);
	UEX_CPU_ZERO(cpu_set_1);

	UEX_CPU_SET(cpu_set_0, 0);
	UEX_CPU_SET(cpu_set_0, 1);
	UEX_CPU_SET(cpu_set_1, 0);
	UEX_CPU_SET(cpu_set_1, 1);

	uex_init();

	uex_thread_t thread1 = uex_thread_create_affinity(
			&thread1_main, 0, &cpu_set_0);
	uex_thread_t thread2 = uex_thread_create_affinity(
			&thread2_main, 0, &cpu_set_1);

	for (int i=0; i<32; i++) {
		fprintf(stdout, "main: %d\n", uex_thread_self());
		uex_yield();
	}
}
