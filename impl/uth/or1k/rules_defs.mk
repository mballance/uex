
ifneq (1,$(RULES))
UTH_OR1K_SRC_DIR := $(dir $(lastword $(MAKEFILE_LIST)))

SRC_DIRS += $(UTH_OR1K_SRC_DIR)

UTH_OR1K_SRC := $(notdir $(wildcard $(UTH_OR1K_SRC_DIR)/*.S))

else

libuth_or1k.o : $(UTH_OR1K_SRC:.S=.o)
	rm -f $@
	$(LD) -r -o $@ $^

endif
