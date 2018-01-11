/****************************************************************************
 * uex_sys.svh
 ****************************************************************************/

typedef class uex_thread;
typedef class uex_mutex;
typedef class uex_cond;
typedef class uex_mem_services;

/**
 * Class: uex_sys
 * 
 * TODO: Add class documentation
 */
class uex_sys extends uex_sys_main implements uex_mem_services;

	string					m_name;
	chandle					m_sys_h;
	int unsigned			m_sys_id;
	
	uex_thread				m_thread_l[$];
	uex_mutex				m_mutex_l[$];
	uex_cond				m_cond_l[$];
	int unsigned			m_active;
	int unsigned			m_active_core;
	uex_thread				m_blocked[$];
	semaphore				m_irq_sem = new(1);
	uex_mem_services		m_mem_services;
	uex_mem_services		m_cores[$];
	uex_sys_main			m_main = null;
//	semaphore				m_irq_sem = new(1);
	
	function new(string name="", uex_sys_main main=null);
		m_name = name;
		m_sys_id = uex_pkg::m_global.add_sys(this);
		
		if (main != null) begin
			m_main = main;
		end else begin
			m_main = this;
		end
	
		// Create a new host-side representation
		m_sys_h = _uex_sys_new(m_sys_id);
	endfunction

	// Run 
	task run();
		int unsigned prev_active_sys = uex_pkg::m_global.get_active_sys();
		
		// Set system context
		uex_pkg::m_global.set_active_sys(m_sys_id);
		m_main.main();
		uex_pkg::m_global.set_active_sys(prev_active_sys);
	endtask

	virtual task main();
		// Assume the user has extended the class
		$display("UEX Error: uex_sys::main for %0s has not been overridden", m_name);
		$stop();
	endtask
	
	task uex_irq(int unsigned id);
		m_irq_sem.get(1);
		_uex_irq(id);
		m_irq_sem.put(1);		
	endtask

	virtual task iowrite8(
		byte unsigned data, 
		longint unsigned addr);
		m_cores[m_active_core].iowrite8(data, addr);
	endtask
	
	virtual task ioread8(
		output byte unsigned data, 
		input longint unsigned addr);
		m_cores[m_active_core].ioread8(data, addr);
	endtask
	
	virtual task iowrite16(
		shortint unsigned data, 
		longint unsigned addr);
		m_cores[m_active_core].iowrite16(data, addr);
	endtask
	
	virtual task ioread16(
		output shortint unsigned data, 
		input longint unsigned addr);
		m_cores[m_active_core].ioread16(data, addr);
	endtask
	
	virtual task iowrite32(
		int unsigned data, 
		longint unsigned addr);
		m_cores[m_active_core].iowrite32(data, addr);
	endtask
	
	virtual task ioread32(
		output int unsigned data, 
		input longint unsigned addr);
		m_cores[m_active_core].ioread32(data, addr);
	endtask
	
	virtual task iowrite64(
		longint unsigned data, 
		longint unsigned addr);
		m_cores[m_active_core].iowrite64(data, addr);
	endtask
	
	virtual task ioread64(
		output longint unsigned data, 
		input longint unsigned addr);
		m_cores[m_active_core].ioread64(data, addr);
	endtask	
	
	virtual function longint unsigned ioalloc(
		int unsigned 	sz,
		int unsigned	align,
		int unsigned	flags);
		return m_cores[m_active_core].ioalloc(sz, align, flags);
	endfunction
	
	virtual function void iofree(longint unsigned p);
		m_cores[m_active_core].iofree(p);
	endfunction
	
endclass

import "DPI-C" function chandle _uex_sys_new(int unsigned id);

task automatic _uex_iowrite8(byte unsigned data, longint unsigned addr);
	m_global.iowrite8(data, addr);
endtask
export "DPI-C" task _uex_iowrite8;
	
task automatic _uex_ioread8(output byte unsigned data, input longint unsigned addr);
	m_global.ioread8(data, addr);
endtask
export "DPI-C" task _uex_ioread8;
	
task automatic _uex_iowrite16(shortint unsigned data, longint unsigned addr);
	m_global.iowrite16(data, addr);
endtask
export "DPI-C" task _uex_iowrite16;
	
task automatic _uex_ioread16(output shortint unsigned data, input longint unsigned addr);
	m_global.ioread16(data, addr);
endtask
export "DPI-C" task _uex_ioread16;
	
task automatic _uex_iowrite32(int unsigned data, longint unsigned addr);
	m_global.iowrite32(data, addr);
endtask
export "DPI-C" task _uex_iowrite32;
	
task automatic _uex_ioread32(output int unsigned data, input longint unsigned addr);
	m_global.ioread32(data, addr);
endtask	
export "DPI-C" task _uex_ioread32;

task automatic _uex_iowrite64(int unsigned data, longint unsigned addr);
	m_global.iowrite64(data, addr);
endtask
export "DPI-C" task _uex_iowrite64;
	
task automatic _uex_ioread64(output int unsigned data, input longint unsigned addr);
	m_global.ioread64(data, addr);
endtask	
export "DPI-C" task _uex_ioread64;

function automatic longint unsigned _uex_ioalloc(
	int unsigned sz, 
	int unsigned align,
	int unsigned flags);
	return m_global.ioalloc(sz, align, flags);
endfunction
export "DPI-C" function _uex_ioalloc;

import "DPI-C" context task _uex_irq(int unsigned id);

