/****************************************************************************
 * uex_ve_mem_access.svh
 ****************************************************************************/

/**
 * Class: uex_ve_mem_access
 * 
 * TODO: Add class documentation
 */
class uex_ve_mem_access implements uex_mem_services;
	int unsigned n_write8, n_write16, n_write32, n_write64;
	int unsigned n_read8, n_read16, n_read32, n_read64;

	function new();
	endfunction
	
	function int unsigned num_mem_accesses();
		return (n_write8+n_write16+n_write32+n_write64 +
				n_read8+n_read16+n_read32+n_read64);
	endfunction

	virtual task iowrite8(
			byte unsigned data, 
			longint unsigned addr);
		n_write8++;
	endtask
	
	 virtual task ioread8(
			output byte unsigned data, 
			input longint unsigned addr);
		n_read8++;
	 endtask
	
	virtual task iowrite16(
			shortint unsigned data, 
			longint unsigned addr);
		n_write16++;
	endtask
	
	virtual task ioread16(
			output shortint unsigned data, 
			input longint unsigned addr);
		n_read16++;
	endtask
	
	virtual task iowrite32(
			int unsigned data, 
			longint unsigned addr);
		n_write32++;
	endtask
	
	virtual task ioread32(
			output int unsigned data, 
			input longint unsigned addr);
		n_read32++;
	endtask
	
	virtual task iowrite64(
			longint unsigned data, 
			longint unsigned addr);
		n_write64++;
	endtask
	
	virtual task ioread64(
			output longint unsigned data, 
			input longint unsigned addr);	
		n_read64++;
	endtask

	virtual function longint unsigned ioalloc(
			int unsigned 	sz,
			int unsigned	align,
			int unsigned	flags);
	endfunction
	
	virtual function void iofree(longint unsigned p);	
	endfunction
	
endclass


