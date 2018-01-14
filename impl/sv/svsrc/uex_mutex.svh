/****************************************************************************
 * uex_mutex.svh
 ****************************************************************************/

/**
 * Class: uex_mutex
 * 
 * TODO: Add class documentation
 */
class uex_mutex;
	int unsigned		m_mid;
	semaphore			m_sem;
		
	function new(int unsigned mid);
		m_mid = mid;
		m_sem = new(1);
	endfunction
		
	task lock();
		uex_active_s sleeping_thread = m_global.get_active();
		m_sem.get(1);
		m_global.set_active(sleeping_thread);
	endtask
		
	task unlock();
		m_sem.put(1);
	endtask
endclass 

function automatic void _uex_create_mutex(int unsigned mid);
		
endfunction
export "DPI-C" function _uex_create_mutex;
	
function automatic void _uex_destroy_mutex(int unsigned cid);
endfunction
export "DPI-C" function _uex_destroy_mutex;
	
function automatic int unsigned _uex_mutex_init();
	return m_global.alloc_mutex();
endfunction
export "DPI-C" function _uex_mutex_init;
	
task automatic _uex_mutex_lock(int unsigned mid);
	// Block the active thread
	m_global.lock_mutex(mid);
endtask
export "DPI-C" task _uex_mutex_lock;
	
task automatic _uex_mutex_unlock(int unsigned mid);
	// Block the active thread
	m_global.unlock_mutex(mid);
endtask
export "DPI-C" task _uex_mutex_unlock;
	
function automatic int unsigned _uex_cond_init();
	return m_global.alloc_cond();
endfunction
export "DPI-C" function _uex_cond_init;
	
task automatic _uex_cond_wait(
	int unsigned		cid,
	int unsigned		mid);
	m_global.cond_wait(cid, mid);
endtask
export "DPI-C" task _uex_cond_wait;
	
task automatic _uex_cond_signal(
	int unsigned		cid);
	m_global.cond_signal(cid);
endtask
export "DPI-C" task _uex_cond_signal;
	
import "DPI-C" context task _uex_thread_main(
	chandle				main_f,
	chandle				ud);


