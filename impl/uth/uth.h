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

void uth_yield(void);

uth_thread_t *uth_create(uth_main_f f, void *ud);


#endif /* INCLUDED_UTH_H */
