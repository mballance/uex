
include $(SIMSCRIPTS_DIR)/mkfiles/plusargs.mk

TB=uex_ve_tb
DPI_OBJS_LIBS += test_sw.o uex.o
	
MK_INCLUDES += $(GOOGLETEST_UVM)/src/rules_defs.mk
	
UEX_SRC := \
	$(notdir $(wildcard $(SIM_DIR)/../../*.c)) \
	uex_sys_dpi.c
		
	
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

	