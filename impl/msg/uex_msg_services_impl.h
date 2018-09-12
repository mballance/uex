/**
 *
 */
#ifndef INCLUDED_UEX_MSG_SERVICES_IMPL_H
#define INCLUDED_UEX_MSG_SERVICES_IMPL_H
#include <stdarg.h>

typedef struct uex_msg_s *uex_msg_hndl;

#ifdef __cplusplus
extern "C" {
#endif


void uex_info_low_impl(uex_msg_hndl *h, const char *fmt, va_list ap);

void uex_info_mid_impl(uex_msg_hndl *h, const char *fmt, va_list ap);

void uex_info_high_impl(uex_msg_hndl *h, const char *fmt, va_list ap);

void uex_error_impl(uex_msg_hndl *h, const char *fmt, va_list ap);

void uex_fatal_impl(uex_msg_hndl *h, const char *fmt, va_list ap);

#ifdef __cplusplus
}
#endif


#endif /* INCLUDED_UEX_MSG_SERVICES_IMPL_H */

