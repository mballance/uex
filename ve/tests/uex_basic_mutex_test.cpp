#include "gtest/gtest.h"
#include "uex.h"
#include <stdio.h>

static uex_mutex_t			m_mutex;

static int thread1_main(void *ud) {
	for (int i=0; i<16; i++) {
		fprintf(stdout, "thread1: --> lock\n");
		uex_mutex_lock(&m_mutex);
		fprintf(stdout, "thread1: <-- lock\n");
		uex_yield();
		fprintf(stdout, "thread1: --> unlock\n");
		uex_mutex_unlock(&m_mutex);
		fprintf(stdout, "thread1: <-- unlock\n");
		uex_yield();
	}
	return 0;
}

static int thread2_main(void *ud) {
	for (int i=0; i<16; i++) {
		fprintf(stdout, "thread2: --> lock\n");
		uex_mutex_lock(&m_mutex);
		fprintf(stdout, "thread2: <-- lock\n");
		uex_yield();
		fprintf(stdout, "thread2: --> unlock\n");
		uex_mutex_unlock(&m_mutex);
		fprintf(stdout, "thread2: <-- unlock\n");
		uex_yield();
	}
	return 0;
}

TEST(UEX,basic_mutex_test) {
	fprintf(stdout, "Hello there\n");
	fflush(stdout);

	uex_mutex_init(&m_mutex);

	uex_thread_t thread1 = uex_thread_create(&thread1_main, 0);
	uex_thread_t thread2 = uex_thread_create(&thread2_main, 0);


	for (int i=0; i<32; i++) {
		fprintf(stdout, "main: %d\n", uex_thread_self());
		uex_yield();
	}
}
