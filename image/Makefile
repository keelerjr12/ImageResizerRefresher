# Makefile

# Compiler
CXX ?= g++

# Compiler flags
CXXFLAGS ?= --std=c++20 -Wall -Werror -pedantic -g -Wno-sign-compare -Wno-comment

# Directories
SRC ?= src
BIN ?= bin
DATA ?= data
INC ?= -I../matrix/src -I../unit_test_framework

# Run unit tests
test: Image_tests.exe 
	./$(BIN)/Image_tests.exe 

Image_tests.exe: $(SRC)/Image_tests.cpp $(SRC)/Image.cpp $(SRC)/Image_test_helpers.cpp
	$(CXX) $(CXXFLAGS) $(INC) $^ -o $(BIN)/$@

# Disable built-in Makefile rules
.SUFFIXES:

clean:
	rm -rvf $(BIN)/*.exe $(BIN)/*.out.txt $(BIN)/*.out.ppm $(BIN)/*.dSYM $(BIN)/*.stackdump

# Run style check tools
CPD ?= /usr/um/pmd-6.0.1/bin/run.sh cpd
OCLINT ?= /usr/um/oclint-0.13/bin/oclint
FILES := \
  $(SRC)/Image.cpp \
  $(SRC)/Image_tests.cpp
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
