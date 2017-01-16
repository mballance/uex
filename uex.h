/****************************************************************************
 * uex.h
 ****************************************************************************/
#ifndef INCLUDED_UEX_H
#define INCLUDED_UEX_H
/**
 * Defines:
 * - uex_thread_t
 * - uex_cond_t
 * - uex_mutex_t
 */
#include "uex_sys.h"

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************
 * uex_init()
 *
 * Called once prior to invoking the root thread
 ********************************************************************/
void uex_init(void);

/********************************************************************
 * Threads
 ********************************************************************/
typedef int (*uex_thread_f)(void *);

uex_thread_t uex_thread_create(
		uex_thread_f		main_f,
		void				*ud);

int uex_thread_join(uex_thread_t t);

void uex_yield(void);

uex_thread_t uex_thread_self(void);

void uex_mutex_init(uex_mutex_t *m);

void uex_mutex_lock(uex_mutex_t *m);

void uex_mutex_unlock(uex_mutex_t *m);

void uex_cond_init(uex_cond_t *c);

void uex_cond_wait(uex_cond_t *c, uex_mutex_t *m);

void uex_cond_signal(uex_cond_t *c);

/********************************************************************
 * Interrupts
 ********************************************************************/

typedef void (*uex_irq_f)(void *);

/**
 * uex_get_irq()
 *
 * Client function that
 */
int32_t uex_get_irq(uint32_t *drv_id);

void uex_set_irq_handler(
		uint32_t 		irq,
		uex_irq_f		*f,
		void			*ud);

#ifdef __cplusplus
}
#endif

#endif /* INCLUDED_UEX_H */
