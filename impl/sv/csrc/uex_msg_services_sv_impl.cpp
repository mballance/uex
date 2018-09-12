
#include "uex_msg_services_impl.h"
#include <stdio.h>

void uex_info_low_impl(uex_msg_hndl *h, const char *fmt, va_list ap) {
	fprintf(stdout, "[INFO] ");
	vfprintf(stdout, fmt, ap);
	fprintf(stdout, "\n");
}

void uex_info_mid_impl(uex_msg_hndl *h, const char *fmt, va_list ap) {
	fprintf(stdout, "[INFO] ");
	vfprintf(stdout, fmt, ap);
	fprintf(stdout, "\n");
}

void uex_info_high_impl(uex_msg_hndl *h, const char *fmt, va_list ap) {
	fprintf(stdout, "[INFO] ");
	vfprintf(stdout, fmt, ap);
	fprintf(stdout, "\n");
}

void uex_error_impl(uex_msg_hndl *h, const char *fmt, va_list ap) {
	fprintf(stdout, "[ERROR] ");
	vfprintf(stdout, fmt, ap);
	fprintf(stdout, "\n");
}

void uex_fatal_impl(uex_msg_hndl *h, const char *fmt, va_list ap) {
	fprintf(stdout, "[FATAL] ");
	vfprintf(stdout, fmt, ap);
	fprintf(stdout, "\n");
}

