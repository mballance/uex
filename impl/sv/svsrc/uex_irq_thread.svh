/****************************************************************************
 * uex_irq_thread.svh
 ****************************************************************************/

/**
 * Class: uex_irq_thread
 * 
 * TODO: Add class documentation
 */
class uex_irq_thread implements uex_run_if;
	int				m_cond_id;
	int				m_mutex_id;
	bit				m_irq;
	int unsigned	m_irq_id;

	function new();
		m_cond_id = _uex_alloc_sem(0);
		m_mutex_id = _uex_alloc_sem(1);
	endfunction

	virtual task run();
		forever begin
			while (m_irq == 0) begin
				_uex_mutex_lock(m_mutex_id);
				_uex_cond_wait(m_cond_id, m_mutex_id);
				_uex_mutex_unlock(m_mutex_id);
			end
			_uex_irq(m_irq_id);
			m_irq = 0;
		end
	endtask
	
	task irq(int irq_id);
		_uex_mutex_lock(m_mutex_id);
		m_irq = 1;
		m_irq_id = irq_id;
		_uex_cond_signal(m_cond_id, 1);
		_uex_mutex_unlock(m_mutex_id);
	endtask

endclass


