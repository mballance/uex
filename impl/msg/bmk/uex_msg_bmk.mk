
UEX_MSG_BMK_DIR := $(dir $(lastword $(MAKEFILE_LIST)))

ifneq (1,$(RULES))

SRC_DIRS += $(UEX_MSG_BMK_DIR) $(UEX_MSG_BMK_DIR)/..
UEX_MSG_BMK_SRC = $(notdir $(wildcard $(UEX_MSG_BMK_DIR)/*.c))

UEX_OBJS += $(UEX_MSG_BMK_SRC:.c=.o)

else # Rules


endif
