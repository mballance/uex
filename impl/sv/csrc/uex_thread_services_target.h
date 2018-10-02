/*
 * uex_thread_services_target.h
 *
 *  Created on: Jan 7, 2018
 *      Author: ballance
 */

#ifndef IMPL_SV_UEX_THREAD_SERVICES_TARGET_H_
#define IMPL_SV_UEX_THREAD_SERVICES_TARGET_H_
#include <stdint.h>

typedef uint32_t uex_thread_t;

typedef struct uex_mutex_s {
	uint32_t			sem_id;
	uint32_t			sem_refcnt;
} uex_mutex_t;

typedef struct uex_cond_s {
	uint32_t			sem_id;
	uint32_t			waiters;
} uex_cond_t;

typedef struct uex_event_s {
	uint32_t			sem_id;
} uex_event_t;


#endif /* IMPL_SV_UEX_THREAD_SERVICES_TARGET_H_ */
