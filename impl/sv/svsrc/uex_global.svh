/****************************************************************************
 * uex_global.svh
 ****************************************************************************/

typedef class uex_sys;
typedef class uex_thread;
typedef class uex_mutex;
typedef class uex_cond;
typedef class uex_mem_services;

/**
 * Class: uex_global
 * 
 * TODO: Add class documentation
 */
class uex_global implements uex_mem_services;
	uex_sys					m_sys[$];
	int unsigned			m_active_sys;
	uex_thread				m_thread_l[$];
	uex_mutex				m_mutex_l[$];
	uex_cond				m_cond_l[$];
	int unsigned			m_active;
	uex_thread				m_blocked[$];
	uex_mem_services		m_mem_services;
	uex_mem_services		m_cores[$];	

	function new();

	endfunction
	
	function int unsigned get_active_sys();
		return m_active_sys;
	endfunction

	function void set_active_sys(int unsigned sys_id);
		m_active_sys = sys_id;
	endfunction
	
	function int unsigned add_sys(uex_sys sys);
		int unsigned sys_id = m_sys.size();
		m_sys.push_back(sys);
		return sys_id;
	endfunction
	
	function int unsigned alloc_mutex();
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
	
	function int unsigned alloc_cond();
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

	function int unsigned alloc_thread(
		chandle			main_f,
		chandle			ud);
		int tid_i = -1;
		uex_thread t;

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
		
		return tid_i;
	endfunction
	
	task start_thread(int unsigned tid);
		fork
			m_thread_l[tid].run();
		join_none		
	endtask
	
	task join_thread(int unsigned tid);
		uex_thread t = m_thread_l[tid];
		
		if (t != null) begin
			t.do_join();
		end		
	endtask
	
	task yield_thread();
		int unsigned sleeping_thread = m_active;
		// Allow another active thread to run
		#0;
		m_active = sleeping_thread;		
	endtask
	
	function void free_thread(int unsigned tid);
		m_thread_l[tid] = null;
	endfunction
	
	task lock_mutex(int unsigned mid);
		m_mutex_l[mid].lock();
	endtask
	
	task unlock_mutex(int unsigned mid);
		m_mutex_l[mid].unlock();
	endtask
	
	task cond_wait(int unsigned cid, int unsigned mid);
		m_mutex_l[mid].unlock();
		m_cond_l[cid].cond_wait();
		m_mutex_l[mid].lock();
	endtask
	
	task cond_signal(int unsigned cid);
		m_cond_l[cid].cond_signal();
	endtask

	static function uex_global init();
		uex_global ret = new;
		return ret;
	endfunction

	virtual task iowrite8(
			byte unsigned data, 
			longint unsigned addr);
		m_sys[m_active_sys].iowrite8(data, addr);
	endtask
	
	virtual task ioread8(
			output byte unsigned data, 
			input longint unsigned addr);
		m_sys[m_active_sys].ioread8(data, addr);
	endtask
	
	virtual task iowrite16(
			shortint unsigned data, 
			longint unsigned addr);
		m_sys[m_active_sys].iowrite16(data, addr);
	endtask
	
	virtual task ioread16(
			output shortint unsigned data, 
			input longint unsigned addr);
		m_sys[m_active_sys].ioread16(data, addr);
	endtask
	
	virtual task iowrite32(
			int unsigned data, 
			longint unsigned addr);
		m_sys[m_active_sys].iowrite32(data, addr);
	endtask
	
	virtual task ioread32(
			output int unsigned data, 
			input longint unsigned addr);
		m_sys[m_active_sys].ioread32(data, addr);
	endtask
	
	virtual task iowrite64(
			longint unsigned data, 
			longint unsigned addr);
		m_sys[m_active_sys].iowrite64(data, addr);
	endtask
	
	virtual task ioread64(
			output longint unsigned data, 
			input longint unsigned addr);
		m_sys[m_active_sys].ioread64(data, addr);
	endtask

	virtual function longint unsigned ioalloc(
			int unsigned 	sz,
			int unsigned	align,
			int unsigned	flags);
		return m_sys[m_active_sys].ioalloc(sz, align, flags);
	endfunction
	
	virtual function void iofree(longint unsigned p);
		m_sys[m_active_sys].iofree(p);
	endfunction
	
endclass


import "DPI-C" context function int _uex_init();
function automatic int do_uex_init();
	// Create a representation for the main thread
	uex_thread t = new(0, null, null);
	m_global.m_thread_l.push_back(t);
		
	return _uex_init();
endfunction
int _initialized = do_uex_init();


