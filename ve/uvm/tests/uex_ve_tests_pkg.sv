

`include "uvm_macros.svh"
package uex_ve_tests_pkg;
	import uvm_pkg::*;
	import uex_ve_env_pkg::*;
	import uex_pkg::*;
	
	`include "uex_ve_mem_access.svh"
	
	`include "uex_ve_test_base.svh"
	`include "uex_ve_irq_test.svh"
	`include "uex_ve_multicore_test.svh"
	
endpackage
