
EXEC_ASSEMBLER ?= montador

TESTS_EXEC ?= utests

CXX = g++

CXXFLAGS = -g -Wall -pedantic

BUILD_DIR ?= build
SRC_DIRS ?= src 

MAIN := src/$(EXEC_ASSEMBLER).cpp
SRCS := $(wildcard src/*.cpp)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

# Existe alguma maneira mais concisa de fazer o que está na linha debaixo?
TEST_SRCS := $(wildcard tests/*.test.cpp) $(wildcard tests/**/*.test.cpp)
TEST_OBJS := $(filter-out build/src/$(EXEC_ASSEMBLER).cpp.o, $(OBJS)) \
						 $(TEST_SRCS:%=$(BUILD_DIR)/%.o)

all: assembler 
# all: assembler simulator


####################################
# Executável principal             #
####################################
assembler: $(BUILD_DIR)/$(EXEC_ASSEMBLER) 
	@echo " > main: Done $@ => $<"
	@cp $< $(EXEC_ASSEMBLER)
	@echo " ------------------------"

$(BUILD_DIR)/$(EXEC_ASSEMBLER): $(OBJS) $(MAIN)
	@echo ">> main: Building executable"
	@$(CXX) $(CXXFLAGS) $(OBJS) -o $@

# cpp sources
$(BUILD_DIR)/%.cpp.o: %.cpp
	@echo ">> main: Building source file: $<"
	@echo " > main: Output file: $@\n"
	@$(MKDIR_P) $(dir $@)
	@$(CXX) $(CXXFLAGS) -c $< -o $@


####################################
# Executável do testes unitários	 #
####################################
utests: $(BUILD_DIR)/$(TESTS_EXEC)
	@echo " > test: Build done"
	@echo " ------------------------"

$(BUILD_DIR)/$(TESTS_EXEC): $(TEST_OBJS)
	@echo ">> test: Building TEST executable $@"
	@$(CXX) $(CXXFLAGS) $(TEST_OBJS) -o $@

$(BUILD_DIR)/%.test.cpp.o: %.test.cpp
	@echo ">> test: Building test source: $<"
	@echo " > test: Output file: $@\n"
	@$(MKDIR_P) $(dir $@)
	@$(CXX) $(CXXFLAGS) -c $< -o $@


.PHONY: clean test main

clean:
	rm -fr $(BUILD_DIR)/* $(EXEC_ASSEMBLER) $(TESTS_EXEC)


MKDIR_P ?= mkdir -p