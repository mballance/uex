
include $(SIMSCRIPTS_DIR)/mkfiles/plusargs.mk

TB=uex_ve_tb
DPI_OBJS_LIBS += test_sw.o uex.o
	
MK_INCLUDES += $(GOOGLETEST_UVM)/src/googletest_uvm.mk
MK_INCLUDES += $(UEX)/uex.mk
MK_INCLUDES += $(UEX)/impl/sv/uex_env_sv.mk
	
TEST_SW_SRC := $(notdir $(wildcard $(SIM_DIR)/../tests/sw/*.cpp))

CFLAGS += -I$(UEX)
CXXFLAGS += -I$(UEX)
CXXFLAGS += -I$(UEX)/impl/sv
CFLAGS += -I$(UEX)/impl/sv
CXXFLAGS += -I$(SIM_DIR)/../tests/sw

include $(SIMSCRIPTS_DIR)/mkfiles/common_sim.mk

test_sw.o : $(TEST_SW_SRC:.cpp=.o)
	$(LD) -r -o $@ $^
	
uex.o : $(UEX_SRC:.c=.o)
	$(LD) -r -o $@ $^

%.o : %.cc
	$(CXX) -c $(CXXFLAGS) -o $@ $^

%.o : $(SIM_DIR)/../tests/sw/%.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ $^
	
%.o : $(UEX)/impl/sv/%.c
	$(CC) -c $(CFLAGS) -o $@ $^
	
%.o : $(UEX)/%.c
	$(CC) -c $(CFLAGS) -o $@ $^

	
