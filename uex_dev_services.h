
#ifdef __cplusplus
extern "C" {
#endif

struct uex_device_s;

/**
 * Sets the UEX device tree. Called during initialization.
 *
 * Note: the handle to the device array is stored, and
 * must not be freed by the caller
 */
void uex_set_devtree(
		struct uex_device_s		*devices,
		uint32_t				n_devices);

#ifdef __cplusplus
}
#endif
