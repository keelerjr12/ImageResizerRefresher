# Makefile
PROG := p2_image_resizer

# Compiler
CXX ?= g++

# Compiler flags
CXXFLAGS ?= --std=c++20 -Wall -Werror -pedantic -g -Wno-sign-compare -Wno-comment

# Directories
SRC_DIRS := src
BUILD_DIR := build
BIN_DIR := bin
DATA := data

# Get source files
PROG_SRC := $(shell find $(SRC_DIRS) -name '$(PROG).cpp' )
SRCS := $(shell find $(SRC_DIRS) -name '*.cpp' -and ! -name '*.test.*' -and ! -name $(PROG).cpp -or -name '*.c' -or -name '*.s' )
TESTS := $(shell find $(SRC_DIRS) -name '*.test.cpp' -or -name '*.test.c' -or -name '*.test.s' )

# Add object ext
PROG_OBJ :=  $(PROG_SRC:%=$(BUILD_DIR)/%.o)
OBJS :=  $(SRCS:%=$(BUILD_DIR)/%.o)
TEST_OBJS := $(TESTS:%=$(BUILD_DIR)/%.o)

TEST_TARGETS := $(TESTS:%=$(BIN_DIR)/%.exe)

DEPS := $(OBJS:.o=.d)
DEPS += $(TEST_OBJS:.o=.d)

INC_DIRS :=  $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPP_FLAGS := $(INC_FLAGS) #-MMD -MP

# Do actual compiling, linking, and running
all: $(BIN_DIR)/$(PROG).exe
	./$^

$(BIN_DIR)/$(PROG).exe: $(PROG_OBJ) $(OBJS)
	$(CXX) $(CPP_FLAGS) $(CXXFLAGS) $^ -o $@
	#diff $(DATA)/dog_4x5.out.ppm $(DATA)/dog_4x5.correct.ppm

tests: $(TEST_TARGETS)

$(BIN_DIR)/%.test.cpp.exe: $(BUILD_DIR)/%.test.cpp.o $(OBJS)
	@mkdir -p $(@D)
	$(CXX) $(CPP_FLAGS) $(CXXFLAGS) $^ -o $@
	./$@

$(BUILD_DIR)/%.cpp.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CPP_FLAGS) $(CXXFLAGS) -c $^ -o $@

clean:
	rm -r $(BUILD_DIR) $(BIN_DIR)

# Disable built-in Makefile rules
.SUFFIXES:

.PHONY: clean all

-include $(DEPS)
