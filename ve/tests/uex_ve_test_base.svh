
import "DPI-C" context task uex_test_main(
	string 			testname,
	output int		status);
	
class uex_ve_test_base extends uvm_test;
	
	`uvm_component_utils(uex_ve_test_base)
	
	uex_ve_env				m_env;
	
	function new(string name, uvm_component parent=null);
		super.new(name,parent);
	endfunction
	
	function void build_phase(uvm_phase phase);
		super.build_phase(phase);
	
		m_env = uex_ve_env::type_id::create("m_env", this);
	endfunction
	
	task run_phase(uvm_phase phase);
		int status;
		string sw_testname;
		
		if (!$value$plusargs("SW_TESTNAME=%s", sw_testname)) begin
			`uvm_fatal(get_name(), "Failed to specify +SW_TESTNAME=<name>");
		end
		
		phase.raise_objection(this, "Main");
		uex_test_main(sw_testname, status);
		phase.drop_objection(this, "Main");
		
		$display("NOTE: test status: %0d", status);
	endtask
	
endclass

