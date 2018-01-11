
class uex_ve_irq_test extends uex_ve_test_base;
	
	`uvm_component_utils(uex_ve_irq_test)
	
	/****************************************************************
	 * Data Fields
	 ****************************************************************/
	
	/****************************************************************
	 * new()
	 ****************************************************************/
	function new(string name, uvm_component parent=null);
		super.new(name, parent);
	endfunction

	/****************************************************************
	 * build_phase()
	 ****************************************************************/
	function void build_phase(uvm_phase phase);
		super.build_phase(phase);
	endfunction

	/****************************************************************
	 * connect_phase()
	 ****************************************************************/
	function void connect_phase(uvm_phase phase);
		super.connect_phase(phase);
	endfunction

	/****************************************************************
	 * run_phase()
	 ****************************************************************/
	task run_phase(uvm_phase phase);
		fork
			super.run_phase(phase);
			begin
				repeat (16) begin
					#1;
//TODO:					uex_pkg::uex_irq();
				end
			end
		join
		// TODO: Launch any local behavior
	endtask
	
endclass



