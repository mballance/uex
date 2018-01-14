/****************************************************************************
 * uex_global.svh
 ****************************************************************************/

typedef class uex_sys;
typedef class uex_thread;
typedef class uex_mutex;
typedef class uex_cond;
typedef class uex_mem_services;

typedef struct {
	int unsigned	active_sys;
	int unsigned	active_thread;
	int unsigned	active_core;
} uex_active_s;

/**
 * Class: uex_global
 * 
 * TODO: Add class documentation
 */
class uex_global implements uex_mem_services;
	uex_sys					m_sys[$];
	uex_active_s			m_active;
	uex_thread				m_thread_l[$];
	uex_mutex				m_mutex_l[$];
	uex_cond				m_cond_l[$];
	uex_thread				m_blocked[$];
	uex_mem_services		m_mem_services;
	uex_mem_services		m_cores[$];	
	
	static uex_global		m_global;

	function new();

	endfunction
	
	function int unsigned get_active_sys();
		return m_active.active_sys;
	endfunction

	function void set_active_sys(int unsigned sys_id);
		m_active.active_sys = sys_id;
	endfunction
	
	function uex_active_s get_active();
		return m_active;
	endfunction
	
	function void set_active(uex_active_s active);
		m_active = active;
	endfunction
	
	function uex_thread get_active_thread();
		return m_thread_l[m_active.active_thread];
	endfunction
	
	function int unsigned get_nprocs();
		return m_sys[m_active.active_sys].m_cores.size();
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
		chandle				main_f,
		chandle				ud,
		longint unsigned	affinity);
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

		t = new(tid_i, main_f, ud, affinity);
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
		uex_active_s sleeping_thread = get_active();
		uex_thread active_thread = get_active_thread();
		$display("-- YIELD: %0d affinity='h%08h",
				sleeping_thread.active_thread,
				active_thread.m_affinity);
				
		// Allow another active thread to run
		// active holds the sys and current core-id
		// TODO: possibly swap to another core?
		#0;
		
		// Rescheduling this thread. 
		// Decide whether to assign it to a different core
		begin
			int unsigned current_core = sleeping_thread.active_core;
			uex_sys sys = m_sys[sleeping_thread.active_sys];
			int new_core = -1;

			for (int i=0; i<sys.m_cores.size(); i++) begin
				current_core = ((current_core+1) % sys.m_cores.size());
				
				if (active_thread.m_affinity & (1 << current_core)) begin
					new_core = current_core;
					break;
				end
			end
			
			if (new_core != -1) begin
				$display("Moving to core %0d", new_core);
				sleeping_thread.active_core = new_core;
			end else begin
				$display("Staying withcore %0d", sleeping_thread.active_core);
			end
		end
		
		set_active(sleeping_thread);
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
		m_sys[m_active.active_sys].m_cores[m_active.active_core].iowrite8(data, addr);
	endtask
	
	virtual task ioread8(
			output byte unsigned data, 
			input longint unsigned addr);
		m_sys[m_active.active_sys].m_cores[m_active.active_core].ioread8(data, addr);
	endtask
	
	virtual task iowrite16(
			shortint unsigned data, 
			longint unsigned addr);
		m_sys[m_active.active_sys].m_cores[m_active.active_core].iowrite16(data, addr);
	endtask
	
	virtual task ioread16(
			output shortint unsigned data, 
			input longint unsigned addr);
		m_sys[m_active.active_sys].m_cores[m_active.active_core].ioread16(data, addr);
	endtask
	
	virtual task iowrite32(
			int unsigned data, 
			longint unsigned addr);
		m_sys[m_active.active_sys].m_cores[m_active.active_core].iowrite32(data, addr);
	endtask
	
	virtual task ioread32(
			output int unsigned data, 
			input longint unsigned addr);
		m_sys[m_active.active_sys].m_cores[m_active.active_core].ioread32(data, addr);
	endtask
	
	virtual task iowrite64(
			longint unsigned data, 
			longint unsigned addr);
		m_sys[m_active.active_sys].m_cores[m_active.active_core].iowrite64(data, addr);
	endtask
	
	virtual task ioread64(
			output longint unsigned data, 
			input longint unsigned addr);
		m_sys[m_active.active_sys].m_cores[m_active.active_core].ioread64(data, addr);
	endtask

	virtual function longint unsigned ioalloc(
			int unsigned 	sz,
			int unsigned	align,
			int unsigned	flags);
		return m_sys[m_active.active_sys].m_cores[m_active.active_core].ioalloc(sz, align, flags);
	endfunction
	
	virtual function void iofree(longint unsigned p);
		m_sys[m_active.active_sys].m_cores[m_active.active_core].iofree(p);
	endfunction

	static function uex_global dflt();
		if (m_global == null) begin
			m_global = new();
		end
		return m_global;
	endfunction
endclass


import "DPI-C" context function int _uex_init();
function automatic int do_uex_init();
	// Create a representation for the main thread
	uex_thread t = new(0, null, null, 0);
	uex_global::dflt().m_thread_l.push_back(t);
		
	return _uex_init();
endfunction
int _initialized = do_uex_init();


