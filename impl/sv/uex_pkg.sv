/****************************************************************************
 * uex_pkg.sv
 ****************************************************************************/

/**
 * Package: uex_pkg
 * 
 * TODO: Add package documentation
 */
package uex_pkg;
	`include "uex_memalloc.svh"
	`include "uex_mem_services.svh"
	
	typedef class uex_thread;
	typedef class uex_mutex;
	typedef class uex_cond;
	
	uex_thread				m_thread_l[$];
	uex_mutex				m_mutex_l[$];
	uex_cond				m_cond_l[$];
	int unsigned			m_active;
	uex_thread				m_blocked[$];
	semaphore				m_irq_sem = new(1);
	uex_mem_services		m_mem_services;
	
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
			m_active = m_tid; // preload so yield sets active correctly
			_uex_yield();
			_uex_thread_main(m_main_f, m_ud);
			m_join.put(1);
		endtask
		
		task do_join();
			int unsigned sleeping_thread = m_active;
			m_join.get(1);
			
			// Delete thread once another thread joins
			m_thread_l[m_tid] = null;
			
			m_active = sleeping_thread;
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
		chandle				ud,
		output int unsigned	tid);
		uex_thread t;
		int tid_i = -1;

		// Support a maximum 16k threads before looping around
		if (m_thread_l.size() >= 16384) begin
			for (int i=0; i<m_thread_l.size(); i++) begin
				if (m_thread_l[i] == null) begin
					tid_i = i;
					break;
				end
			end
		end
		
		if (tid_i == -1) begin
			tid_i = m_thread_l.size();
			m_thread_l.push_back(null);
		end

		t = new(tid_i, main_f, ud);
		m_thread_l[tid_i] = t;
	
		// Return the TID
		tid = tid_i;
	
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
	
	task automatic _uex_thread_join(int unsigned tid);
		uex_thread t = m_thread_l[tid];
		
		if (t != null) begin
			t.do_join();
		end
	endtask
	export "DPI-C" task _uex_thread_join;
	
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
	function automatic int do_uex_init();
		// Create a representation for the main thread
		uex_thread t = new(0, null, null);
		m_thread_l.push_back(t);
		
		return _uex_init();
	endfunction
	int _initialized = do_uex_init();
	
	task automatic uex_irq(int unsigned id);
		m_irq_sem.get(1);
		_uex_irq(id);
		m_irq_sem.put(1);
	endtask
	import "DPI-C" context task _uex_irq(int unsigned id);

	task automatic _uex_iowrite8(byte unsigned data, longint unsigned addr);
		m_mem_services.iowrite8(data, addr);
	endtask
	export "DPI-C" task _uex_iowrite8;
	
	task automatic _uex_ioread8(output byte unsigned data, input longint unsigned addr);
		m_mem_services.ioread8(data, addr);
	endtask
	export "DPI-C" task _uex_ioread8;
	
	task automatic _uex_iowrite16(shortint unsigned data, longint unsigned addr);
		m_mem_services.iowrite16(data, addr);
	endtask
	export "DPI-C" task _uex_iowrite16;
	
	task automatic _uex_ioread16(output shortint unsigned data, input longint unsigned addr);
		m_mem_services.ioread16(data, addr);
	endtask
	export "DPI-C" task _uex_ioread16;
	
	task automatic _uex_iowrite32(int unsigned data, longint unsigned addr);
		m_mem_services.iowrite32(data, addr);
	endtask
	export "DPI-C" task _uex_iowrite32;
	
	task automatic _uex_ioread32(output int unsigned data, input longint unsigned addr);
		m_mem_services.ioread32(data, addr);
	endtask	
	export "DPI-C" task _uex_ioread32;
	
	task automatic _uex_ioalloc(
		int unsigned sz, 
		int unsigned align,
		int unsigned flags);
	endtask
	export "DPI-C" task _uex_ioalloc;

endpackage


