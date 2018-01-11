/*
 * uex_sys_services_sv_impl.c
 *
 *  Created on: Jan 7, 2018
 *      Author: ballance
 */
#include "uex_sys_services.h"
#include "uex_sys_services_sv_impl.h"
#include "uex_dpi.h"
#include <stdio.h>
#include <stdexcept>
#include <stdlib.h>
#include <string.h>


static svScope					m_scope = 0;
static uint32_t					prv_nprocs = 0;

#ifdef __cplusplus
extern "C" {
#endif
#ifdef __cplusplus
}
#endif

void *uex_svScope() {
	return m_scope;
}

/********************************************************************
 * uex_sys_init()
 ********************************************************************/
void uex_sys_init(void) {
	// TODO: Probe number of available processors
}

/********************************************************************
 * uex_get_nprocs()
 *
 * Returns the number of processors available on the system.
 ********************************************************************/
uint32_t uex_get_nprocs(void) {
	return prv_nprocs;
}


// Exported DPI task
//int _uex_irq(uint32_t id) {
//
//	try {
//		if (m_handler) {
//			m_handler(m_handler_ud, id);
//		} else {
//			fprintf(stdout, "FATAL: no handler\n");
//		}
//	} catch (std::runtime_error &e) {
//		svAckDisabledState();
//		return 1;
//	}
//
//	return 0;
//}
//
//void uex_sv_set_interrupt_handler(
//		uex_interrupt_handler	h,
//		void					*ud) {
//	m_handler = h;
//	m_handler_ud = ud;
//}

