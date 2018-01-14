#include "gtest/gtest.h"
#include "uex.h"
#include <stdio.h>

int thread1_main(void *ud) {
	for (int i=0; i<16; i++) {
		fprintf(stdout, "thread1_main %d\n", uex_thread_self());
		uex_yield();
	}
	return 0;
}

int thread2_main(void *ud) {
	for (int i=0; i<16; i++) {
		fprintf(stdout, "thread2_main %d\n", uex_thread_self());
		uex_yield();
	}
	return 0;
}

TEST(UEX,basic_thread_test) {

	fprintf(stdout, "Hello there\n");
	fflush(stdout);

	uex_init();

	uex_thread_t thread1 = uex_thread_create(&thread1_main, 0);
	uex_thread_t thread2 = uex_thread_create(&thread2_main, 0);

	for (int i=0; i<32; i++) {
		fprintf(stdout, "main: %d\n", uex_thread_self());
		uex_yield();
	}
}
