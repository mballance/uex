/****************************************************************************
 * uex_mem_alloc_services.svh
 ****************************************************************************/

/**
 * Class: uex_mem_alloc_services
 * 
 * TODO: Add class documentation
 */
interface class uex_mem_alloc_services;


	pure virtual function longint unsigned ioalloc(
		int unsigned 	sz,
		int unsigned	align,
		int unsigned	flags);
	
	pure virtual function void iofree(longint unsigned p);
	

endclass


