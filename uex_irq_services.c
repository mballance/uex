/****************************************************************************
 * uex_irq_services.c
 ****************************************************************************/
#include "uex_irq_services.h"
#include "uex_msg_services.h"
#include "uex_dev_services.h"
#include "uex_config.h"

void uex_trigger_irq(uint32_t devid) {
	uex_dev_t *dev = uex_get_device(devid);
	if (dev) {
		if (dev->irq) {
			dev->irq(dev);
		} else {
			uex_error(0, "Error: irq not registered for devid=%d", devid);
		}
	} else {
		uex_error(0, "Error: devid %d is invalid", devid);
	}
}
