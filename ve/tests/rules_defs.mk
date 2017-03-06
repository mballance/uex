
UEX_TESTS_SRC_DIR := $(dir $(lastword $(MAKEFILE_LIST)))

ifneq (1,$(RULES))

SRC_DIRS += $(UEX_TESTS_SRC_DIR)

UEX_TESTS_SRC := $(notdir $(wildcard $(UEX_TESTS_SRC_DIR)/*.cpp))

else

libuex_tests.o : $(UEX_TESTS_SRC:.cpp=.o)
	rm -f $@
	$(LD) -r -o $@ $^

endif
