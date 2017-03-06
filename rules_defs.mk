
UEX_SRC_DIR := $(dir $(lastword $(MAKEFILE_LIST)))

ifneq (1,$(RULES))

SRC_DIRS += $(UEX_SRC_DIR)

UEX_SRC := $(notdir $(wildcard $(UEX_SRC_DIR)/*.c))

BUILD_COMPILE_TARGETS += print

else

.PHONY: print
print :
	echo "This is print"

libuex.o : $(UEX_SRC:.c=.o)
	rm -f $@
	$(LD) -r -o $@ $^

endif

