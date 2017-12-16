
ifneq (1,$(RULES))
UTH_RISCV_SRC_DIR := $(dir $(lastword $(MAKEFILE_LIST)))

SRC_DIRS += $(UTH_RISCV_SRC_DIR)

UTH_RISCV_SRC := $(notdir $(wildcard $(UTH_RISCV_SRC_DIR)/*.S))

LIBUTH_THREADING := libuex_uth_riscv.o libuex_uth.o

else

libuex_uth_riscv.o : $(UTH_RISCV_SRC:.S=.o) 
	rm -f $@
	$(LD) -r -o $@ $^

endif
