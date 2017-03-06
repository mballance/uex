
ifneq (1,$(RULES))
UTH_SRC_DIR := $(dir $(lastword $(MAKEFILE_LIST)))

SRC_DIRS += $(UTH_SRC_DIR)

UTH_SRC := uth.c

UEX_UTH_SRC := uex_sys_uth.c

else

libuth.o : $(UTH_SRC:.c=.o)
	rm -f $@
	$(LD) -r -o $@ $^

libuex_uth.o : $(UEX_UTH_SRC:.c=.o)
	rm -f $@
	$(LD) -r -o $@ $^


endif
