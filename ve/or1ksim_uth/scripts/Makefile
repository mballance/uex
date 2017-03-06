
include $(SIMSCRIPTS_DIR)/mkfiles/plusargs.mk

CXX=or1k-elf-g++
CC=or1k-elf-gcc
LD=or1k-elf-ld

LIBGCC:=$(shell $(CC) -print-libgcc-file-name -mcompat-delay)
LIBC:=$(dir $(LIBGCC))/../../../../../or1k-elf/lib/compat-delay/libc.a
LIBCXX:=$(dir $(LIBGCC))/../../../../../or1k-elf/lib/compat-delay/libstdc++.a
LIBOR1K:=$(dir $(LIBGCC))/../../../../../or1k-elf/lib/compat-delay/libor1k.a
LIBOR1KSIM:=$(dir $(LIBGCC))/../../../../../or1k-elf/lib/compat-delay/libboard-or1ksim.a


TB=uex_ve_tb
DPI_OBJS_LIBS += test_sw.o uex.o
	
MK_INCLUDES += $(GOOGLETEST_UVM)/src/rules_defs.mk
MK_INCLUDES += $(UEX)/rules_defs.mk
MK_INCLUDES += $(UEX)/impl/uth/rules_defs.mk
MK_INCLUDES += $(UEX)/impl/uth/or1k/rules_defs.mk
MK_INCLUDES += $(SIM_DIR)/../tests/rules_defs.mk
	
TEST_LIBS += libuex.o googletest.o libuex_uth.o
TEST_LIBS += libuth.o libuth_or1k.o
TEST_LIBS += libuex_tests.o

BUILD_COMPILE_TARGETS += $(TEST_LIBS)
RUN_TARGETS += runtest

CXXFLAGS +=  -D_POSIX_PATH_MAX=256
CXXFLAGS += -DGTEST_HAS_POSIX_RE=0

SW_TESTNAME := $(call get_plusarg,SW_TESTNAME,$(PLUSARGS))

include $(SIMSCRIPTS_DIR)/mkfiles/common_sim.mk

runtest :
	$(CXX) -c $(CXXFLAGS) -o testmain.o $(SIM_DIR)/src/testmain.cpp \
		-DTESTNAME_STR=\"$(TESTNAME)\" -DSW_TESTNAME_STR=\"$(SW_TESTNAME)\"
	$(CXX) -o testmain.elf testmain.o -mboard=or1ksim \
		$(foreach lib,$(TEST_LIBS),$(BUILD_DIR)/$(lib))
	or1k-sim -f $(SIM_DIR)/sim.cfg testmain.elf 2>&1 | tee simx.log

	
