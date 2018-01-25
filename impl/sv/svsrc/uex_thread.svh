/****************************************************************************
 * uex_thread.svh
 ****************************************************************************/

/**
 * Class: uex_thread
 * 
 * TODO: Add class documentation
 */
class uex_thread;
	int unsigned		m_tid;
	chandle				m_main_f;
	chandle				m_ud;
	semaphore			m_join = new(0);
	longint unsigned	m_affinity;
	int					m_core;
	int					m_sys;
		
	function new(
		int unsigned 		tid,
		chandle				main_f,
		chandle				ud,
		longint unsigned	affinity);
		m_tid = tid;
		m_main_f = main_f;
		m_ud = ud;
		m_affinity = affinity;
	endfunction
		
	task run();
		uex_active_s active = m_global.get_active();
		process p = process::self();
		
		active.active_thread = m_tid;
		m_global.set_active(active); // preload so yield sets active correctly
		
		m_global.set_thread_process(p, this);

		_uex_yield();
		_uex_thread_main(m_main_f, m_ud);
		m_join.put(1);
		
		m_global.clr_thread_process(p);
	endtask
		
	task do_join();
		uex_active_s sleeping_thread = m_global.get_active();
		m_join.get(1);
			
		// Delete thread once another thread joins
		m_global.free_thread(m_tid);
			
		m_global.set_active(sleeping_thread);
	endtask
endclass 

task automatic _uex_create_thread(
	chandle					main_f,
	chandle					ud,
	output int unsigned		tid,
	input longint unsigned	affinity);
	uex_thread t;

	// Return the TID
	tid = m_global.alloc_thread(main_f, ud, affinity);
	m_global.start_thread(tid);
	
endtask
export "DPI-C" task _uex_create_thread;

function automatic int unsigned _uex_thread_self();
	uex_active_s active = m_global.get_active();
	return active.active_thread;
endfunction
export "DPI-C" function _uex_thread_self;
	
task automatic _uex_thread_join(int unsigned tid);
	m_global.join_thread(tid);
endtask
export "DPI-C" task _uex_thread_join;

task automatic _uex_yield();
	m_global.yield_thread();
endtask
export "DPI-C" task _uex_yield;

import "DPI-C" context task _uex_thread_main(
	chandle				main_f,
	chandle				ud);
