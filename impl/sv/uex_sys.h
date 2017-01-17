/****************************************************************************
 * uex_sys.h
 *
 * uex_sys for SystemVerilog
 ****************************************************************************/
#ifndef INCLUDED_UEX_SYS_H
#define INCLUDED_UEX_SYS_H
#include <stdint.h>

typedef uint32_t uex_thread_t;
typedef uint32_t uex_mutex_t;
typedef uint32_t uex_cond_t;


// SystemVerilog-specific functions
#ifdef __cplusplus
extern "C" {
#endif

typedef void (*uex_interrupt_handler)(void *ud);

void uex_sv_set_interrupt_handler(
		uex_interrupt_handler	h,
		void					*ud);

#ifdef __cplusplus
}
#endif


#endif /* INCLUDED_UEX_SYS_H */
