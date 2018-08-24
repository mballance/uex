/****************************************************************************
 * uex_irq_services.c
 ****************************************************************************/
#include "uex_irq_services.h"
#include "uex_msg_services.h"
#include "uex_dev_services.h"
#include "uex_config.h"
#include <stdio.h>


void uex_trigger_irq(uint32_t devid) {
	uex_dev_t *dev = uex_get_device(devid);
	if (dev) {
		if (dev->irq) {
			dev->irq(dev);
		} else {
			fprintf(stdout, "Error: irq not registered for devid=%d\n", devid);
		}
	} else {
		fprintf(stdout, "Error: devid %d is invalid\n", devid);
	}
}
