/****************************************************************************
 * uex_mem_access_services.svh
 ****************************************************************************/

/**
 * Class: uex_mem_access_services
 * 
 * TODO: Add class documentation
 */
interface class uex_mem_access_services;

	pure virtual task iowrite8(
		byte unsigned data, 
		longint unsigned addr);
	
	pure virtual task ioread8(
		output byte unsigned data, 
		input longint unsigned addr);
	
	pure virtual task iowrite16(
		shortint unsigned data, 
		longint unsigned addr);
	
	pure virtual task ioread16(
		output shortint unsigned data, 
		input longint unsigned addr);
	
	pure virtual task iowrite32(
		int unsigned data, 
		longint unsigned addr);
	
	pure virtual task ioread32(
		output int unsigned data, 
		input longint unsigned addr);
	
	pure virtual task iowrite64(
		longint unsigned data, 
		longint unsigned addr);
	
	pure virtual task ioread64(
		output longint unsigned data, 
		input longint unsigned addr);

endclass


