
ifneq (1,$(RULES))
UTH_SRC_DIR := $(dir $(lastword $(MAKEFILE_LIST)))

SRC_DIRS += $(UTH_SRC_DIR)

UTH_SRC := uth.c

UEX_UTH_SRC := $(notdir $(wildcard $(UTH_SRC_DIR)/*.c))

else

libuex_uth.o : $(UEX_UTH_SRC:.c=.o)
	rm -f $@
	$(LD) -r -o $@ $^


endif
