/****************************************************************************
 * uex_cond.svh
 ****************************************************************************/

/**
 * Class: uex_cond
 * 
 * TODO: Add class documentation
 */
class uex_cond;
	int unsigned		m_cid;
	int unsigned		m_waiters;
	semaphore			m_sem;
		
	function new(int unsigned cid);
		m_cid = cid;
		m_sem = new(0);
	endfunction
		
	task cond_wait();
//		int unsigned sleeping_thread = m_active;
//		m_waiters++;
//		m_sem.get(1);
//		m_active = sleeping_thread;
	endtask
		
	task cond_signal();
		m_sem.put(m_waiters);
		m_waiters = 0;
	endtask
		
endclass 


