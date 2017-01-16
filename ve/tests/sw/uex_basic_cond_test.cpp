#include "gtest/gtest.h"
#include "uex.h"
#include <stdio.h>

static uex_mutex_t			m_data_ready_mutex;
static uex_cond_t			m_data_ready_cond;
static int					m_data_ready;
static uex_mutex_t			m_data_taken_mutex;
static uex_cond_t			m_data_taken_cond;
static int					m_data_taken;

// Producer thread
static int thread1_main(void *ud) {

	for (int i=0; i<16; i++) {
		fprintf(stdout, "--> Producing Data\n");
		uex_mutex_lock(&m_data_ready_mutex);
		m_data_ready = 1;
		uex_cond_signal(&m_data_ready_cond);
		uex_mutex_unlock(&m_data_ready_mutex);
		fprintf(stdout, "<-- Producing Data\n");

		fprintf(stdout, "--> Waiting for consumption\n");
		uex_mutex_lock(&m_data_taken_mutex);
		if (!m_data_taken) {
			fprintf(stdout, "  --> not taken; blocking\n");
			uex_cond_wait(&m_data_taken_cond, &m_data_taken_mutex);
			fprintf(stdout, "  <-- not taken; blocking\n");
		} else {
			fprintf(stdout, " -- already taken\n");
		}
		fprintf(stdout, " -- m_data_taken=%d\n", m_data_taken);
		m_data_taken = 0;
		uex_mutex_unlock(&m_data_taken_mutex);
		fprintf(stdout, "<-- Waiting for consumption\n");
	}

	return 0;
}

// Consumer thread
static int thread2_main(void *ud) {
	for (int i=0; i<16; i++) {
		fprintf(stdout, "--> Waiting for data\n");
		uex_mutex_lock(&m_data_ready_mutex);
		if (!m_data_ready) {
			fprintf(stdout, " --> not ready; blocking\n");
			uex_cond_wait(&m_data_ready_cond, &m_data_ready_mutex);
			fprintf(stdout, " <-- not ready; blocking\n");
		} else {
			fprintf(stdout, " -- already ready\n");
		}
		fprintf(stdout, " -- m_data_ready=%d\n", m_data_ready);
		m_data_ready = 0;
		uex_mutex_unlock(&m_data_ready_mutex);
		fprintf(stdout, "<-- Waiting for data\n");

		fprintf(stdout, "--> Signaling Consumption\n");
		uex_mutex_lock(&m_data_taken_mutex);
		m_data_taken = 1;
		uex_cond_signal(&m_data_taken_cond);
		uex_mutex_unlock(&m_data_taken_mutex);
		fprintf(stdout, "<-- Signaling Consumption\n");
	}
	return 0;
}

TEST(UEX,basic_cond_test) {
	fprintf(stdout, "Hello there\n");
	fflush(stdout);

	uex_mutex_init(&m_data_ready_mutex);
	uex_cond_init(&m_data_ready_cond);
	m_data_ready = 0;
	uex_mutex_init(&m_data_taken_mutex);
	uex_cond_init(&m_data_taken_cond);
	m_data_taken = 0;

	uex_thread_t thread1 = uex_thread_create(&thread1_main, 0);
	uex_thread_t thread2 = uex_thread_create(&thread2_main, 0);

	for (int i=0; i<32; i++) {
		fprintf(stdout, "main: %d\n", uex_thread_self());
		uex_yield();
	}
}
