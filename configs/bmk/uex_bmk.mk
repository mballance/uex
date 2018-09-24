
UEX_BMK_CONFIG_DIR := $(dir $(lastword $(MAKEFILE_LIST)))
UEX_DIR := $(abspath $(UEX_BMK_CONFIG_DIR)/../../)

ifneq (1,$(RULES))

UEX_BMK_MK_INCLUDES += $(UEX_DIR)/uex.mk
UEX_BMK_MK_INCLUDES += $(UEX_DIR)/impl/mem/baremetal/uex_mem_baremetal.mk
UEX_BMK_MK_INCLUDES += $(UEX_DIR)/impl/msg/bmk/uex_msg_bmk.mk
UEX_BMK_MK_INCLUDES += $(UEX_DIR)/impl/sys/bmk/uex_sys_bmk.mk
UEX_BMK_MK_INCLUDES += $(UEX_DIR)/impl/threading/bmk/uex_threading_bmk.mk

include $(UEX_BMK_MK_INCLUDES)

else # Rules

include $(UEX_BMK_MK_INCLUDES)

endif
