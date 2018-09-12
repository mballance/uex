/****************************************************************************
 * uex_global.svh
 ****************************************************************************/

typedef class uex_sys;
typedef class uex_thread;
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
	uex_thread				m_thread_map[process];
	uex_thread				m_blocked[$];
	uex_mem_services		m_mem_services;
	uex_mem_services		m_cores[$];	
	semaphore				m_semaphore_l[$];
	
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
		process p = process::self();
		
		if (m_thread_map.exists(p)) begin
			return m_thread_map[p];
		end else begin
			$display("Error: no thread for current process");
			return null;
		end		
	endfunction
	
	function uex_thread get_thread(int tid);
		return m_thread_l[tid];
	endfunction
	
	function int unsigned get_nprocs();
		return m_sys[m_active.active_sys].m_cores.size();
	endfunction
	
	function int unsigned add_sys(uex_sys sys);
		int unsigned sys_id = m_sys.size();
		m_sys.push_back(sys);
		return sys_id;
	endfunction
	
	function int unsigned alloc_thread(
		uex_run_if			run_if,
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

		t = new(tid_i, run_if, affinity);
		m_thread_l[tid_i] = t;
		
		return tid_i;
	endfunction
	
	function int unsigned alloc_sem(int unsigned init);
		int unsigned sem_i = 0;
		semaphore s;
		
		if (m_semaphore_l.size() >= 16384) begin
			for (int i=0; i<m_semaphore_l.size(); i++) begin
				if (m_semaphore_l[i] == null) begin
					sem_i = (i+1);
					break;
				end
			end
		end
		
		if (sem_i == 0) begin
			sem_i = (m_semaphore_l.size()+1);
			m_semaphore_l.push_back(null);
		end
	
		s = new(init);
		m_semaphore_l[sem_i-1] = s;
		
		return sem_i;
	endfunction
	
	function semaphore get_sem(int sem_id);
		return m_semaphore_l[sem_id-1];
	endfunction
	
	function void free_sem(int sem_id);
		m_semaphore_l[sem_id-1] = null;
	endfunction
		
	
	task start_thread(int unsigned tid);
		fork
			begin
				m_thread_l[tid].run();
			end
		join_none		
	endtask
	
	task join_thread(int unsigned tid);
		uex_thread t = m_thread_l[tid];
		
		if (t != null) begin
			t.do_join();
		end		
	endtask
	
	function void set_thread_process(process p, uex_thread t);
		m_thread_map[p] = t;
	endfunction
	
	function void clr_thread_process(process p);
		m_thread_map.delete(p);
	endfunction
	
	task yield_thread();
		uex_thread t = get_active_thread();
		$display("--> YIELD: %0d %0d affinity='h%08h",
				t.m_tid, t.m_core, t.m_affinity);
				
		// Allow another active thread to run
		// active holds the sys and current core-id
		// TODO: possibly swap to another core?
		#0;
		
		// Rescheduling this thread. 
		// Decide whether to assign it to a different core
		begin
			int unsigned current_core = t.m_core;
			uex_sys sys = m_sys[t.m_sys];
			int new_core = -1;

			for (int i=0; i<sys.m_cores.size(); i++) begin
				current_core = ((current_core+1) % sys.m_cores.size());
				
				if (t.m_affinity & (1 << current_core)) begin
					new_core = current_core;
					break;
				end
			end
			
			if (new_core != -1) begin
				$display("Moving to core %0d", new_core);
				t.m_core = new_core;
			end else begin
				$display("Staying withcore %0d", t.m_core);
			end
		end
		
		$display("<-- YIELD: %0d %0d affinity='h%08h",
				t.m_tid, t.m_core, t.m_affinity);
		
//		set_active(sleeping_thread);
	endtask
	
	function void free_thread(int unsigned tid);
		m_thread_l[tid] = null;
	endfunction
	
	static function uex_global init();
		uex_global ret = new;
		return ret;
	endfunction
	
	function uex_mem_services get_active_core();
		uex_thread t = get_active_thread();
		return m_sys[m_active.active_sys].m_cores[t.m_core];
	endfunction
	
	task lock_core();
		uex_thread t = get_active_thread();
		_uex_mutex_lock(m_sys[m_active.active_sys].m_core_mutex_ids[t.m_core]);
	endtask
	
	task unlock_core();
		uex_thread t = get_active_thread();
		_uex_mutex_unlock(m_sys[m_active.active_sys].m_core_mutex_ids[t.m_core]);
	endtask

	virtual task iowrite8(
			byte unsigned data, 
			longint unsigned addr);
		lock_core();
		get_active_core().iowrite8(data, addr);
		unlock_core();
	endtask
	
	virtual task ioread8(
			output byte unsigned data, 
			input longint unsigned addr);
		lock_core();
		get_active_core().ioread8(data, addr);
		unlock_core();
	endtask
	
	virtual task iowrite16(
			shortint unsigned data, 
			longint unsigned addr);
		lock_core();
		get_active_core().iowrite16(data, addr);
		unlock_core();
	endtask
	
	virtual task ioread16(
			output shortint unsigned data, 
			input longint unsigned addr);
		lock_core();
		get_active_core().ioread16(data, addr);
		unlock_core();
	endtask
	
	virtual task iowrite32(
			int unsigned data, 
			longint unsigned addr);
		lock_core();
		get_active_core().iowrite32(data, addr);
		unlock_core();
	endtask
	
	virtual task ioread32(
			output int unsigned data, 
			input longint unsigned addr);
		lock_core();
		get_active_core().ioread32(data, addr);
		unlock_core();
	endtask
	
	virtual task iowrite64(
			longint unsigned data, 
			longint unsigned addr);
		lock_core();
		get_active_core().iowrite64(data, addr);
		unlock_core();
	endtask
	
	virtual task ioread64(
			output longint unsigned data, 
			input longint unsigned addr);
		lock_core();
		get_active_core().ioread64(data, addr);
		unlock_core();
	endtask

	virtual function longint unsigned ioalloc(
			int unsigned 	sz,
			int unsigned	align,
			int unsigned	flags);
		return get_active_core().ioalloc(sz, align, flags);
	endfunction
	
	virtual function void iofree(longint unsigned p);
		get_active_core().iofree(p);
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
	uex_thread t = new(0, null, 0);
	uex_global::dflt().m_thread_l.push_back(t);
	$display("TODO: _uex_init() called");
		
	return _uex_init();
endfunction
int _initialized = do_uex_init();

function automatic int unsigned _uex_alloc_sem(int unsigned init);
	int unsigned ret = m_global.alloc_sem(init);
	return ret;
endfunction
export "DPI-C" function _uex_alloc_sem;

function automatic void _uex_free_sem(int unsigned sem_id);
	m_global.free_sem(sem_id);
endfunction
export "DPI-C" function _uex_free_sem;

task automatic _uex_mutex_lock(int unsigned sem_id);
	m_global.get_sem(sem_id).get(1);
endtask
export "DPI-C" task _uex_mutex_lock;
	
task automatic _uex_mutex_unlock(int unsigned sem_id);
	m_global.get_sem(sem_id).put(1);
endtask
export "DPI-C" task _uex_mutex_unlock;

task automatic _uex_cond_wait(
	int unsigned		c_sem_id,
	int unsigned		m_sem_id);
	// Unlock the mutex
	m_global.get_sem(m_sem_id).put(1);
	
	// Wait for the condition
	m_global.get_sem(c_sem_id).get(1);

	// Lock the mutex
	m_global.get_sem(m_sem_id).get(1);
endtask
export "DPI-C" task _uex_cond_wait;
	
task automatic _uex_cond_signal(
	int unsigned		c_sem_id,
	int unsigned		waiters);
	m_global.get_sem(c_sem_id).put(waiters);
endtask
export "DPI-C" task _uex_cond_signal;
