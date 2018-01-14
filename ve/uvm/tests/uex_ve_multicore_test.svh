/****************************************************************************
 * uex_ve_multicore_test.svh
 ****************************************************************************/

/**
 * Class: uex_ve_multicore_test
 * 
 * TODO: Add class documentation
 */
class uex_ve_multicore_test extends uex_ve_test_base;
	`uvm_component_utils(uex_ve_multicore_test)
	uex_ve_mem_access			m_cores[$];

	function new(string name, uvm_component parent=null);
		super.new(name, parent);
	endfunction

	virtual function uex_sys create_sys();
		uex_sys sys = new("sys", this);
		for (int i=0; i<2; i++) begin
			uex_ve_mem_access core = new();
			sys.m_cores.push_back(core);
			m_cores.push_back(core);
		end
		return sys;
	endfunction
	
	virtual function void report_phase(uvm_phase phase);
		$display("Core0: %0d", m_cores[0].num_mem_accesses());
		$display("Core1: %0d", m_cores[1].num_mem_accesses());
		super.report_phase(phase);
	endfunction

endclass


