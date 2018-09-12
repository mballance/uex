/****************************************************************************
 * uex_msg_services.h
 ****************************************************************************/
#ifndef INCLUDED_UEX_MSG_SERVICES_H
#define INCLUDED_UEX_MSG_SERVICES_H

typedef struct uex_msg_s *uex_msg_hndl;

#ifdef __cplusplus
extern "C" {
#endif


void uex_kpanic(const char *fmt, ...);

void uex_info_low(uex_msg_hndl *h, const char *fmt, ...);

void uex_info_mid(uex_msg_hndl *h, const char *fmt, ...);

void uex_info_high(uex_msg_hndl *h, const char *fmt, ...);

void uex_error(uex_msg_hndl *h, const char *fmt, ...);

void uex_fatal(uex_msg_hndl *h, const char *fmt, ...);

#ifdef __cplusplus
}
#endif

#endif /* INCLUDED_UEX_MSG_SERVICES_H */
