
include $(SIMSCRIPTS_DIR)/mkfiles/plusargs.mk

TB=uex_ve_tb
DPI_OBJS_LIBS += test_sw.o googletest.o uex.o
GOOGLE_TEST_SRC = \
	gtest-all.cc
	
UEX_SRC := \
	$(notdir $(wildcard $(SIM_DIR)/../../*.c)) \
	uex_sys_dpi.c
		
	
TEST_SW_SRC := $(notdir $(wildcard $(SIM_DIR)/../tests/sw/*.cpp))

CXXFLAGS += -I$(SIM_DIR)/../../../googletest
CXXFLAGS += -I$(SIM_DIR)/../../../googletest/include 
CFLAGS += -I$(SIM_DIR)/../..
CXXFLAGS += -I$(SIM_DIR)/../..
CXXFLAGS += -I$(SIM_DIR)/../../impl/sv
CFLAGS += -I$(SIM_DIR)/../../impl/sv
CXXFLAGS += -I$(SIM_DIR)/../tests/sw

include $(SIMSCRIPTS_DIR)/mkfiles/common_sim.mk


googletest.o : $(GOOGLE_TEST_SRC:.cc=.o)
	$(LD) -r -o $@ $^
	
test_sw.o : $(TEST_SW_SRC:.cpp=.o)
	$(LD) -r -o $@ $^
	
uex.o : $(UEX_SRC:.c=.o)
	$(LD) -r -o $@ $^

%.o : $(SIM_DIR)/../../../googletest/src/%.cc
	$(CXX) -c $(CXXFLAGS) -o $@ $^

%.o : $(SIM_DIR)/../tests/sw/%.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ $^
	
%.o : $(SIM_DIR)/../../impl/sv/%.c
	$(CC) -c $(CFLAGS) -o $@ $^
	
%.o : $(SIM_DIR)/../../%.c
	$(CC) -c $(CFLAGS) -o $@ $^
	