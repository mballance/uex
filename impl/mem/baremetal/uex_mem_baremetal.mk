
ifneq (1,$(RULES))
UTH_MEM_BAREMETAL_SRC_DIR := $(dir $(lastword $(MAKEFILE_LIST)))

SRC_DIRS += $(UTH_MEM_BAREMETAL_SRC_DIR)

UTH_MEM_BAREMETAL_SRC := $(notdir $(wildcard $(UTH_MEM_BAREMETAL_SRC_DIR)/*.c))

LIBUTH_MEM := libuth_mem_baremetal.o

else

$(LIBUTH_MEM) : $(UTH_MEM_BAREMETAL_SRC:.c=.o)
	rm -f $@
	$(LD) -r -o $@ $^

endif
