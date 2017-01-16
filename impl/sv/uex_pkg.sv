/****************************************************************************
 * uex_pkg.sv
 ****************************************************************************/

/**
 * Package: uex_pkg
 * 
 * TODO: Add package documentation
 */
package uex_pkg;
	
	typedef class uex_thread;
	typedef class uex_mutex;
	typedef class uex_cond;
	
	uex_thread				m_thread_l[$];
	uex_mutex				m_mutex_l[$];
	uex_cond				m_cond_l[$];
	int unsigned			m_active;
	uex_thread				m_blocked[$];
	
	class uex_thread;
		int unsigned		m_tid;
		chandle				m_main_f;
		chandle				m_ud;
		
		function new(
			int unsigned 	tid,
			chandle			main_f,
			chandle			ud);
			m_tid = tid;
			m_main_f = main_f;
			m_ud = ud;
		endfunction
		
		task run();
			m_active = m_tid; // preload so yield sets active correctly
			_uex_yield();
			_uex_thread_main(m_main_f, m_ud);
			// Delete ourselves
			m_thread_l[m_tid-1] = null;
		endtask
	endclass
	
	class uex_cond;
		int unsigned		m_cid;
		int unsigned		m_waiters;
		semaphore			m_sem;
		
		function new(int unsigned cid);
			m_cid = cid;
			m_sem = new(0);
		endfunction
		
		task cond_wait();
			int unsigned sleeping_thread = m_active;
			m_waiters++;
			m_sem.get(1);
			m_active = sleeping_thread;
		endtask
		
		task cond_signal();
			m_sem.put(m_waiters);
			m_waiters = 0;
		endtask
		
	endclass
	
	class uex_mutex;
		int unsigned		m_mid;
		semaphore			m_sem;
		
		function new(int unsigned mid);
			m_mid = mid;
			m_sem = new(1);
		endfunction
		
		task lock();
			int unsigned sleeping_thread = m_active;
			m_sem.get(1);
			m_active = sleeping_thread;
		endtask
		
		task unlock();
			m_sem.put(1);
		endtask
	endclass
	
	
	task automatic _uex_create_thread(
		chandle				main_f,
		chandle				ud);
		uex_thread t;
		int tid_i = -1;
		
		for (int i=0; i<m_thread_l.size(); i++) begin
			if (m_thread_l[i] == null) begin
				tid_i = i;
				break;
			end
		end
		
		if (tid_i == -1) begin
			tid_i = m_thread_l.size();
			m_thread_l.push_back(null);
		end

		t = new(tid_i+1, main_f, ud);
		m_thread_l[tid_i] = t;
	
		// What is the active thread?
		start_thread(t);
	endtask
	export "DPI-C" task _uex_create_thread;
	
	function automatic int unsigned _uex_thread_self();
		return m_active;
	endfunction
	export "DPI-C" function _uex_thread_self;
	
	task automatic start_thread(uex_thread t);
		fork
			t.run();
		join_none
	endtask
	
	task automatic _uex_yield();
		int unsigned sleeping_thread = m_active;
		// Allow another active thread to run
		#0;
		m_active = sleeping_thread;
	endtask
	export "DPI-C" task _uex_yield;
	
	function automatic void _uex_create_mutex(int unsigned mid);
		
	endfunction
	export "DPI-C" function _uex_create_mutex;
	
	function automatic void _uex_destroy_mutex(int unsigned cid);
	endfunction
	export "DPI-C" function _uex_destroy_mutex;
	
	function automatic int unsigned _uex_mutex_init();
		int mid_i = -1;
		
		for (int i=0; i<m_mutex_l.size(); i++) begin
			if (m_mutex_l[i] == null) begin
				mid_i = i;
				break;
			end
		end
		
		if (mid_i == -1) begin
			mid_i = m_mutex_l.size();
			m_mutex_l.push_back(null);
		end
		
		m_mutex_l[mid_i] = new(mid_i);
		
		return mid_i;
	endfunction
	export "DPI-C" function _uex_mutex_init;
	
	task automatic _uex_mutex_lock(int unsigned mid);
		// Block the active thread
		m_mutex_l[mid].lock();
	endtask
	export "DPI-C" task _uex_mutex_lock;
	
	task automatic _uex_mutex_unlock(int unsigned mid);
		// Block the active thread
		m_mutex_l[mid].unlock();
	endtask
	export "DPI-C" task _uex_mutex_unlock;
	
	function automatic int unsigned _uex_cond_init();
		int cid_i = -1;
		
		for (int i=0; i<m_cond_l.size(); i++) begin
			if (m_cond_l[i] == null) begin
				cid_i = i;
				break;
			end
		end
		
		if (cid_i == -1) begin
			cid_i = m_cond_l.size();
			m_cond_l.push_back(null);
		end
		
		m_cond_l[cid_i] = new(cid_i);
		
		return cid_i;
	endfunction
	export "DPI-C" function _uex_cond_init;
	
	task automatic _uex_cond_wait(
		int unsigned		cid,
		int unsigned		mid);
		m_mutex_l[mid].unlock();
		m_cond_l[cid].cond_wait();
		m_mutex_l[mid].lock();
	endtask
	export "DPI-C" task _uex_cond_wait;
	
	task automatic _uex_cond_signal(
		int unsigned		cid);
		m_cond_l[cid].cond_signal();
	endtask
	export "DPI-C" task _uex_cond_signal;
	
	import "DPI-C" context task _uex_thread_main(
			chandle				main_f,
			chandle				ud);

	import "DPI-C" context function int _uex_init();
	int _initialized = _uex_init();

endpackage

