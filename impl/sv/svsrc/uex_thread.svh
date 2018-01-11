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
		
	function new(
		int unsigned 	tid,
		chandle			main_f,
		chandle			ud);
		m_tid = tid;
		m_main_f = main_f;
		m_ud = ud;
	endfunction
		
	task run();
		m_global.m_active = m_tid; // preload so yield sets active correctly
		_uex_yield();
		_uex_thread_main(m_main_f, m_ud);
		m_join.put(1);
	endtask
		
	task do_join();
		int unsigned sleeping_thread = m_global.m_active;
		m_join.get(1);
			
		// Delete thread once another thread joins
		m_global.free_thread(m_tid);
			
		m_global.m_active = sleeping_thread;
	endtask
endclass 

task automatic _uex_create_thread(
	chandle				main_f,
	chandle				ud,
	output int unsigned	tid);
	uex_thread t;

	
	// Return the TID
	tid = m_global.alloc_thread(main_f, ud);
	m_global.start_thread(tid);
	
endtask
export "DPI-C" task _uex_create_thread;

function automatic int unsigned _uex_thread_self();
	return m_global.m_active;
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

