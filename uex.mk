
UEX_SRC_DIR := $(dir $(lastword $(MAKEFILE_LIST)))

ifneq (1,$(RULES))

SRC_DIRS += $(UEX_SRC_DIR)

UEX_SRC := $(notdir $(wildcard $(UEX_SRC_DIR)/*.c))

SRC_DIRS += $(UEX_SRC_DIR)

LIBUEX := libuex.o

UEX_OBJS += $(UEX_SRC:.c=.o)

else # Rules

libuex.o : $(UEX_OBJS)
	$(Q)rm -f $@
	$(Q)$(LD) -r -o $@ $^
	

endif

