/*
 * uex_irq_services_sv_impl.cpp
 *
 *  Created on: Jan 7, 2018
 *      Author: ballance
 */
#include "uex_thread_services.h"
#include "uex_irq_services.h"
#include "uex_dpi.h"
#include <stdio.h>
#include <stdexcept>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

int _uex_irq(uint32_t id);


#ifdef __cplusplus
}
#endif

static uex_irq_f	m_handler = 0;
static void			*m_handler_ud = 0;

// Exported DPI task
int _uex_irq(uint32_t id) {

	try {
		if (m_handler) {
			m_handler(m_handler_ud);
		} else {
			fprintf(stdout, "FATAL: no handler\n");
		}
	} catch (std::runtime_error &e) {
		svAckDisabledState();
		return 1;
	}

	return 0;
}

/**
 * Implement the handler-setting API
 */
void uex_set_irq_handler(uex_irq_f handler, void *ud) {
	m_handler = handler;
	m_handler_ud = ud;
}

