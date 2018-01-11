
UEX_SV_IMPL_DIR := $(dir $(lastword $(MAKEFILE_LIST)))

ifneq (1,$(RULES))

SRC_DIRS += $(UEX_SV_IMPL_DIR)/csrc

UEX_SV_DPI_SRC := $(notdir $(wildcard $(UEX_SV_IMPL_DIR)/csrc/*.cpp))

DPI_OBJS_LIBS += libuex_sv_dpi.o

else

libuex_sv_dpi.o : $(UEX_SV_DPI_SRC:.cpp=.o)
	rm -f $@
	$(LD) -r -o $@ $^

endif

