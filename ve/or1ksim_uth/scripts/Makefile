
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
MK_INCLUDES += $(UEX)/impl/threading/uth/rules_defs.mk
MK_INCLUDES += $(UEX)/impl/threading/uth/or1k/rules_defs.mk
MK_INCLUDES += $(SIM_DIR)/../tests/rules_defs.mk
	
TEST_LIBS += libuex.o googletest.o libuex_uth.o
TEST_LIBS += libuex_uth_or1k.o
TEST_LIBS += libuex_tests.o

BUILD_COMPILE_TARGETS += $(TEST_LIBS)
RUN_TARGETS += runtest

CXXFLAGS +=  -D_POSIX_PATH_MAX=256
CXXFLAGS += -DGTEST_HAS_POSIX_RE=0
CXXFLAGS += -DGTEST_HAS_STREAM_REDIRECTION=0

SW_TESTNAME := $(call get_plusarg,SW_TESTNAME,$(PLUSARGS))

ifeq (true,$(QUIET))
REDIR := > simx.log 2>&1
else
REDIR := 2>&1 | tee simx.log
endif

include $(SIMSCRIPTS_DIR)/mkfiles/common_sim.mk

runtest :
	$(Q)$(CXX) -c $(CXXFLAGS) -o testmain.o $(SIM_DIR)/src/testmain.cpp \
		-DTESTNAME_STR=\"$(TESTNAME)\" -DSW_TESTNAME_STR=\"$(SW_TESTNAME)\"
	$(Q)$(CC) -c $(CFLAGS) -o sysstubs.o $(SIM_DIR)/src/sysstubs.c 
	$(Q)$(CXX) -o testmain.elf testmain.o sysstubs.o -mboard=or1ksim \
		$(foreach lib,$(TEST_LIBS),$(BUILD_DIR)/$(lib))
	$(Q)echo "break exit" > run.do
	$(Q)echo "run 1000000000 hush" >> run.do
	$(Q)echo "q" >> run.do
	$(Q)or1k-sim -f $(SIM_DIR)/sim.cfg testmain.elf -i < run.do $(REDIR)

	
