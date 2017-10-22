/****************************************************************************
 * uex_mem_services.svh
 ****************************************************************************/

/**
 * Class: uex_mem_services
 * 
 * TODO: Add class documentation
 */
class uex_mem_services;
	
	function new();
	endfunction
	
	virtual task iowrite8(byte unsigned data, longint unsigned addr);
	endtask
	
	virtual task ioread8(
		output byte unsigned data, 
		input longint unsigned addr);
	endtask
	
	virtual task iowrite16(
		shortint unsigned data, 
		longint unsigned addr);
	endtask
	
	virtual task ioread16(
		output shortint unsigned data, 
		input longint unsigned addr);
	endtask
	
	virtual task iowrite32(
		int unsigned data, 
		longint unsigned addr);
	endtask
	
	virtual task ioread32(
		output int unsigned data, 
		input longint unsigned addr);
	endtask
	
	virtual task iowrite64(
		longint unsigned data, 
		longint unsigned addr);
	endtask
	
	virtual task ioread64(
		output longint unsigned data, 
		input longint unsigned addr);
	endtask

	virtual function longint unsigned ioalloc(int unsigned sz);
	endfunction
	
	virtual function void iofree(longint unsigned p);
	endfunction
	


endclass


