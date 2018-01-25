/****************************************************************************
 * uex_delegating_mem_services.svh
 ****************************************************************************/

/**
 * Class: uex_delegating_mem_services
 * 
 * TODO: Add class documentation
 */
class uex_delegating_mem_services implements uex_mem_services;
	uex_mem_access_services			m_access;
	uex_mem_alloc_services			m_alloc;

	function new(
		uex_mem_access_services		access,
		uex_mem_alloc_services		alloc);
		m_access = access;
		m_alloc = alloc;
	endfunction

	virtual task iowrite8(
			byte unsigned data, 
			longint unsigned addr);
		m_access.iowrite8(data, addr);
	endtask
	
	virtual task ioread8(
			output byte unsigned data, 
			input longint unsigned addr);
		m_access.ioread8(data, addr);
	endtask
	
	virtual task iowrite16(
			shortint unsigned data, 
			longint unsigned addr);
		m_access.iowrite16(data, addr);
	endtask
	
	virtual task ioread16(
			output shortint unsigned data, 
			input longint unsigned addr);
		m_access.ioread16(data, addr);
	endtask
	
	virtual task iowrite32(
			int unsigned data, 
			longint unsigned addr);
		m_access.iowrite32(data, addr);
	endtask
	
	virtual task ioread32(
			output int unsigned data, 
			input longint unsigned addr);
		m_access.ioread32(data, addr);
	endtask
	
	virtual task iowrite64(
			longint unsigned data, 
			longint unsigned addr);
		m_access.iowrite64(data, addr);
	endtask
	
	virtual task ioread64(
			output longint unsigned data, 
			input longint unsigned addr);
		m_access.ioread64(data, addr);
	endtask
	
	virtual function longint unsigned ioalloc(
			int unsigned 	sz,
			int unsigned	align,
			int unsigned	flags);
		return m_alloc.ioalloc(sz, align, flags);
	endfunction
	
	virtual function void iofree(longint unsigned p);
		m_alloc.iofree(p);
	endfunction

endclass


