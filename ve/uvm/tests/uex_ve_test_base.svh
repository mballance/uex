

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
		googletest_uvm_pkg::run_all_tests(sw_testname);
		phase.drop_objection(this, "Main");
		
		$display("NOTE: test status: %0d", status);
	endtask
	

	/**
	 * Function: report_phase
	 *
	 * Override from class 
	 */
	virtual function void report_phase(input uvm_phase phase);
		uvm_report_server svr = get_report_server();
		int err = svr.get_severity_count(UVM_ERROR);
		int fatal = svr.get_severity_count(UVM_FATAL);
		string testname;

		void'($value$plusargs("TESTNAME=%s", testname));

		if (err > 0 || fatal > 0) begin
			`uvm_info(get_name(), $psprintf("FAIL: %0s", testname), UVM_LOW);
		end else begin
			`uvm_info(get_name(), $psprintf("PASS: %0s", testname), UVM_LOW);
		end
	endfunction
	
endclass

