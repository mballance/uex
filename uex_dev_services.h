
#ifdef __cplusplus
extern "C" {
#endif

struct uex_device_s;

/**
 * Sets the root device tree. Called during initialization.
 * Calling uex_devtree_init() causes all drivers to be initialized
 *
 * Note: the handle to the device array is stored, and
 * must not be freed by the caller.
 */
void uex_devtree_init(uex_devtree_t *devtree);

/**
 * Utility function to add a sibling to a device tree
 */
void uex_devtree_add_sibling(uex_devtree_t *devtree, uex_devtree_t *sibling);

void uex_devtree_add_child(uex_devtree_t *devtree, uex_devtree_t *child);

#ifdef __cplusplus
}
#endif
