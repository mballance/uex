
UEX_SRC_DIR := $(dir $(lastword $(MAKEFILE_LIST)))

ifneq (1,$(RULES))

SRC_DIRS += $(UEX_SRC_DIR)

UEX_SRC := $(notdir $(wildcard $(UEX_SRC_DIR)/*.c))

SRC_DIRS += $(UEX_SRC_DIR)

else

libuex.o : $(UEX_SRC:.c=.o)
	rm -f $@
	$(LD) -r -o $@ $^

endif

