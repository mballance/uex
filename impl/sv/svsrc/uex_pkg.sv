/****************************************************************************
 * uex_pkg.sv
 ****************************************************************************/

/**
 * Package: uex_pkg
 * 
 * TODO: Add package documentation
 */
package uex_pkg;
	`include "uex_mem_access_services.svh"
	`include "uex_mem_alloc_services.svh"
	`include "uex_mem_services.svh"
	`include "uex_global.svh"
	uex_global				m_global = uex_global::dflt();
	
	`include "uex_sys_main.svh"
	`include "uex_sys.svh"
	`include "uex_cond.svh"
	`include "uex_mutex.svh"
	`include "uex_thread.svh"
	
//	uex_thread				m_thread_l[$];
//	uex_mutex				m_mutex_l[$];
//	uex_cond				m_cond_l[$];
//	int unsigned			m_active;
//	uex_thread				m_blocked[$];
//	uex_mem_services		m_mem_services;
//	uex_mem_services		m_cores[$];
	

endpackage


