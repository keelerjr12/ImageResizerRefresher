# Makefile

# Compiler
CXX ?= g++

# Compiler flags
CXXFLAGS ?= --std=c++20 -Wall -Werror -pedantic -g -Wno-sign-compare -Wno-comment

# Run a regression test
#test: Matrix_public_test.exe Matrix_tests.exe Image_public_test.exe Image_tests.exe processing_public_tests.exe resize.exe
#	./$(BIN)/Matrix_public_test.exe
#	./$(BIN)/Image_public_test.exe
#	./$(BIN)/processing_public_tests.exe
#	./$(BIN)/resize.exe $(DATA)/dog.ppm $(DATA)/dog_4x5.out.ppm 4 5
#	diff $(DATA)/dog_4x5.out.ppm $(DATA)/dog_4x5.correct.ppm

#matrix.o: ./matrix/Matrix.cpp
#	$(CXX) -c $(CXXFLAGS) $^ -o $(BIN)/$@
#
#Matrix_public_test.exe: matrix.o matrix/Matrix_public_test.cpp matrix/Matrix_test_helpers.cpp
#	$(CXX) $(CXXFLAGS) $(LIBS) $^ -o $(BIN)/$@
#	./$(BIN)/$@

BUILD_DIR := build
SRC_DIRS := src

TARGETS := Matrix_public.test.exe #Image_tests.exe Image_public_test.exe processing_public_tests.exe resize.exe

SRCS := $(shell find $(SRC_DIRS) -name '*.cpp' -and ! -name '*.test.*' -or -name '*.c' -or -name '*.s' )
OBJS :=  $(SRCS:%=$(BUILD_DIR)/%.o)

DEPS := $(OBJS:.o=.d)

INC_DIRS :=  $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPP_FLAGS := $(INC_FLAGS) -MMD -MP

$(BUILD_DIR)/$(TARGETS): $(OBJS) ${SRC_DIRS}/matrix/Matrix_public.test.cpp
	$(CXX) -Isrc/unit_test_framework $^ -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.cpp.o:	%.cpp 
	mkdir -p $(dir $@)
	$(CXX) $(CPP_FLAGS) $(CXXFLAGS) -c $^ -o $@
	#./$(BIN)/$@

#Matrix_tests.exe: matrix.o matrix/Matrix.tests.cpp matrix/Matrix_test_helpers.cpp
#	$(CXX) $(CXXFLAGS) $(LIBS) $^ -o $(BIN)/$@
#	./$(BIN)/$@
#
#image.o: ./image/Image.cpp
#	$(CXX) -c $(CXXFLAGS) -Imatrix $^ -o $(BIN)/$@
#
#Image_public_test.exe: $(BIN)/image.o $(BIN)/matrix.o image/Image_public_test.cpp \
#			matrix/Matrix_test_helpers.cpp image/Image_test_helpers.cpp
#	$(CXX) $(CXXFLAGS) $(LIBS) -Imatrix $^ -o $(BIN)/$@
#	./$(BIN)/$@

#Image_tests.exe: $(SRC)/Image_tests.cpp $(SRC)/Matrix.cpp $(SRC)/Image.cpp $(SRC)/Matrix_test_helpers.cpp \
#			$(SRC)/Image_test_helpers.cpp
#	$(CXX) $(CXXFLAGS) $^ -o $(BIN)/$@
#
#processing_public_tests.exe: $(SRC)/processing_public_tests.cpp $(SRC)/Matrix.cpp \
#				$(SRC)/Image.cpp $(SRC)/processing.cpp \
#				$(SRC)/Matrix_test_helpers.cpp $(SRC)/Image_test_helpers.cpp
#	$(CXX) $(CXXFLAGS) $^ -o $(BIN)/$@
#
#resize.exe: $(SRC)/resize.cpp $(SRC)/Matrix.cpp $(SRC)/Image.cpp $(SRC)/processing.cpp
#	$(CXX) $(CXXFLAGS) $^ -o $(BIN)/$@

# Disable built-in Makefile rules
.SUFFIXES:

.PHONY: clean
clean:
	rm -r $(BUILD_DIR)

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
