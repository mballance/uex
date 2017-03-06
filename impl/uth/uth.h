/****************************************************************************
 * uth.h
 ****************************************************************************/
#ifndef INCLUDED_UTH_H
#define INCLUDED_UTH_H
#include <stdint.h>
#include "uth_sys.h"
#include "uth_config.h"

typedef void (*uth_main_f)(void *ud);

typedef struct uth_thread_s {
  uint32_t					status;
  uint32_t					*stack_base;
  uint32_t					stack_sz;
  uth_reg_t					sp;
  uth_main_f				main_f;
  void          			*ud;
  struct uth_thread_s		*next;
} uth_thread_t;

typedef struct uth_mutex_s {
	uth_thread_t			*owner;
	uth_thread_t			*waiters;
} uth_mutex_t;

typedef struct uth_cond_s {
	uth_thread_t			*waiters;
} uth_cond_t;

void uth_yield(void);

uth_thread_t *uth_create(uth_main_f f, void *ud);

uth_thread_t *uth_self(void);

void uth_mutex_init(uth_mutex_t *m);

void uth_mutex_lock(uth_mutex_t *m);

void uth_mutex_unlock(uth_mutex_t *m);

void uth_cond_init(uth_cond_t *c);

void uth_cond_wait(uth_cond_t *c, uth_mutex_t *m);

void uth_cond_signal(uth_cond_t *c);

void uth_cond_signalall(uth_cond_t *c);


#endif /* INCLUDED_UTH_H */
