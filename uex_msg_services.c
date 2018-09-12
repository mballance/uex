/****************************************************************************
 * uex_msg_services.c
 ****************************************************************************/
#include "uex_msg_services.h"
#include "uex_msg_services_impl.h"
#include <stdarg.h>

void uex_kpanic(const char *fmt, ...) {
	// TODO:

}

void uex_info_low(uex_msg_hndl *h, const char *fmt, ...) {
	va_list ap;
	va_start(ap, fmt);

	uex_info_low_impl(h, fmt, ap);

	va_end(ap);
}

void uex_info_mid(uex_msg_hndl *h, const char *fmt, ...) {
	va_list ap;
	va_start(ap, fmt);

	uex_info_mid_impl(h, fmt, ap);

	va_end(ap);
}

void uex_info_high(uex_msg_hndl *h, const char *fmt, ...) {
	va_list ap;
	va_start(ap, fmt);

	uex_info_high_impl(h, fmt, ap);

	va_end(ap);
}

void uex_error(uex_msg_hndl *h, const char *fmt, ...) {
	va_list ap;
	va_start(ap, fmt);

	uex_error_impl(h, fmt, ap);

	va_end(ap);
}

void uex_fatal(uex_msg_hndl *h, const char *fmt, ...) {
	va_list ap;
	va_start(ap, fmt);

	uex_fatal_impl(h, fmt, ap);

	va_end(ap);
}
