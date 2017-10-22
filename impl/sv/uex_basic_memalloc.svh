/****************************************************************************
 * uex_basic_memalloc.svh
 ****************************************************************************/

/**
 * Class: uex_basic_memalloc
 * 
 * TODO: Add class documentation
 */
class uex_basic_memalloc extends uex_memalloc;
	longint unsigned			m_base;
	longint unsigned			m_size;

	function new(longint unsigned base, longint unsigned size);
	endfunction

	virtual function longint unsigned ioalloc(
		int unsigned 	sz,
		int unsigned	align,
		int unsigned	flags);
		
	endfunction
	
	virtual function void iofree(longint unsigned p);
		
	endfunction
	

endclass


