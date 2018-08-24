/****************************************************************************
 * uex_pkg.sv
 ****************************************************************************/

/**
 * Package: uex_pkg
 * 
 * TODO: Add package documentation
 */
package uex_pkg;
	`include "uex_run_if.svh"
	`include "uex_native_runner.svh"
	`include "uex_mem_access_services.svh"
	`include "uex_mem_alloc_services.svh"
	`include "uex_mem_services.svh"
	`include "uex_global.svh"
	uex_global				m_global = uex_global::dflt();

	`include "uex_irq_thread.svh"
	`include "uex_delegating_mem_services.svh"
	`include "uex_sys_main.svh"
	`include "uex_sys.svh"
	`include "uex_thread.svh"
	
endpackage


