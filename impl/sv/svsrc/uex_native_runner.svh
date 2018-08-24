/****************************************************************************
 * uex_native_runner.svh
 ****************************************************************************/

/**
 * Class: uex_native_runner
 * 
 * TODO: Add class documentation
 */
class uex_native_runner implements uex_run_if;
	local chandle			m_main_f;
	local chandle			m_ud;

	function new(
		chandle			main_f,
		chandle			ud);
	endfunction
	
	virtual task run();
		_uex_thread_main(m_main_f, m_ud);
	endtask


endclass


