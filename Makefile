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

DEPS := $(OBJS:.o=.d)
DEPS += $(TEST_OBJS:.o=.d)

INC_DIRS :=  $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPP_FLAGS := $(INC_FLAGS) -MMD -MP

# Do actual compiling, linking, and running
all: $(BIN_DIR)/$(PROG)
	./$^

$(BIN_DIR)/$(PROG): $(PROG_OBJ) $(OBJS)
	$(CXX) $(CPP_FLAGS) $(CXXFLAGS) $^ -o $@
	#diff $(DATA)/dog_4x5.out.ppm $(DATA)/dog_4x5.correct.ppm

tests: $(TEST_OBJS)

$(BUILD_DIR)/%.test.cpp.o: %.test.cpp $(OBJS)
	$(CXX) $(CPP_FLAGS) $(CXXFLAGS) $^ -o $(BIN_DIR)/$(@F)
	./$(BIN_DIR)/$(@F)

$(BUILD_DIR)/%.cpp.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CPP_FLAGS) $(CXXFLAGS) -c $^ -o $@

clean:
	rm -r $(BUILD_DIR)
	
# Disable built-in Makefile rules
.SUFFIXES:

.PHONY: clean all

-include $(DEPS)

# Run style check tools
CPD ?= /usr/um/pmd-6.0.1/bin/run.sh cpd
OCLINT ?= /usr/um/oclint-0.13/bin/oclint
FILES := \
  $(SRC)/Image.cpp \
  $(SRC)/Image_tests.cpp \
  $(SRC)/Matrix.cpp \
  $(SRC)/Matrix_tests.cpp \
  $(SRC)/processing.cpp \
  $(SRC)/resize.cpp
style :
	$(OCLINT) \
    -no-analytics \
    -rule=LongLine \
    -rule=HighNcssMethod \
    -rule=DeepNestedBlock \
    -rule=TooManyParameters \
    -rc=LONG_LINE=90 \
    -rc=NCSS_METHOD=40 \
    -rc=NESTED_BLOCK_DEPTH=4 \
    -rc=TOO_MANY_PARAMETERS=4 \
    -max-priority-1 0 \
    -max-priority-2 0 \
    -max-priority-3 0 \
    $(FILES) \
    -- -xc++ --std=c++20
	$(CPD) \
    --minimum-tokens 100 \
    --language cpp \
    --failOnViolation true \
    --files $(FILES)
	@echo "########################################"
	@echo "EECS 280 style checks PASS"
