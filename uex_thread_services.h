/****************************************************************************
 *
 ****************************************************************************/
#ifndef INCLUDED_UEX_THREAD_SERVICES_H
#define INCLUDED_UEX_THREAD_SERVICES_H
#include "uex_sys.h"
#include "uex_thread_services_target.h"
#include <stdint.h>
#include <string.h>

#ifndef UEX_MAX_CPUS
#define UEX_MAX_CPUS 64
#endif

typedef struct uex_cpu_set_s {
	uint8_t		mask[(UEX_MAX_CPUS-1)/8+1];
} uex_cpu_set_t;

#define UEX_CPU_ZERO(cpu_set) memset((cpu_set).mask, 0, (UEX_MAX_CPUS-1)/8+1);
#define UEX_CPU_SET(cpu_set, bit) (cpu_set).mask[(bit)/8] |= (1 << ((bit)%8))
#define UEX_CPU_CLR(cpu_set, bit) (cpu_set).mask[(bit)/8] &= ~(1 << ((bit)%8))

/********************************************************************
 * Threads
 ********************************************************************/
typedef int (*uex_thread_f)(void *);

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Creates a new thread with default CPU affinity
 */
uex_thread_t uex_thread_create(
		uex_thread_f		main_f,
		void				*ud);

/**
 * Create a new thread with specified CPU affinity
 */
uex_thread_t uex_thread_create_affinity(
		uex_thread_f		main_f,
		void				*ud,
		uex_cpu_set_t		*cpuset);

/**
 * Specifies CPU affinity for a thread
 */
void uex_thread_set_affinity(
		uex_thread_t			thread,
		uex_cpu_set_t			*cpuset);

int uex_thread_join(uex_thread_t t);

void uex_yield(void);

uex_thread_t uex_thread_self(void);

void uex_mutex_init(uex_mutex_t *m);

void uex_mutex_lock(uex_mutex_t *m);

void uex_mutex_unlock(uex_mutex_t *m);

void uex_cond_init(uex_cond_t *c);

void uex_cond_wait(uex_cond_t *c, uex_mutex_t *m);

void uex_cond_signal(uex_cond_t *c);

void uex_cond_signal_async(uex_cond_t *c);

void uex_event_init(uex_event_t *e);

void uex_event_signal(uex_event_t *e);

void uex_event_wait(uex_event_t *e);

#ifdef __cplusplus
}
#endif

#endif /* INCLUDED_UEX_THREAD_SERVICES_H */
