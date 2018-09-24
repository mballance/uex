/****************************************************************************
 * uex_msg_services_bmk.c
 ****************************************************************************/
#include "bmk.h"
#include "uex_msg_services_impl.h"

void uex_info_low_impl(uex_msg_hndl *h, const char *fmt, va_list ap) {
	bmk_info_low_v(fmt, ap);
}

void uex_info_mid_impl(uex_msg_hndl *h, const char *fmt, va_list ap) {
	bmk_info_mid_v(fmt, ap);
}

void uex_info_high_impl(uex_msg_hndl *h, const char *fmt, va_list ap) {
	bmk_info_high_v(fmt, ap);
}

void uex_error_impl(uex_msg_hndl *h, const char *fmt, va_list ap) {
	bmk_error_v(fmt, ap);
}

void uex_fatal_impl(uex_msg_hndl *h, const char *fmt, va_list ap) {
	bmk_fatal_v(fmt, ap);
}

