# 

MAIN_EXEC ?= main

TESTS_EXEC ?= test_exec

CXX = g++

CXXFLAGS = -g

BUILD_DIR ?= build
SRC_DIRS ?= src 

MAIN := src/$(MAIN_EXEC).cpp
SRCS := $(wildcard src/*.cpp)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

TEST_SRCS := $(wildcard tests/*.test.cpp)
TEST_OBJS := $(filter-out build/src/$(MAIN_EXEC).cpp.o, $(OBJS)) \
						 $(TEST_SRCS:%=$(BUILD_DIR)/%.o)

all: main tests


####################################
# Executável principal             #
####################################
main: $(BUILD_DIR)/$(MAIN_EXEC) 
	@echo "  > main: Done $@ => $<"
	@echo "  ------------------------\n"

$(BUILD_DIR)/$(MAIN_EXEC): $(OBJS) $(MAIN)
	@echo ">> main: Building executable"
	@$(CXX) $(CXXFLAGS) $(OBJS) -o $@

# cpp sources
$(BUILD_DIR)/%.cpp.o: %.cpp
	@echo ">> main: Building source file: $< | | match: $*"
	@echo " > main: Output file: $@\n"
	@$(MKDIR_P) $(dir $@)
	@$(CXX) $(CXXFLAGS) -c $< -o $@


####################################
# Executável do testes unitários	 #
####################################
tests: $(BUILD_DIR)/$(TESTS_EXEC)
	@echo " > test: Build done"

$(BUILD_DIR)/$(TESTS_EXEC): $(TEST_OBJS)
	@echo ">> test: Building TEST executable $@"
	@$(CXX) $(CXXFLAGS) $(TEST_OBJS) -o $@

$(BUILD_DIR)/%.test.cpp.o: %.test.cpp
	@echo ">> test: Building test source: $< | match: $*"
	@echo " > test: Output file: $@\n"
	@$(MKDIR_P) $(dir $@)
	@$(CXX) $(CXXFLAGS) -c $< -o $@


.PHONY: clean test main

clean:
	rm -fr $(BUILD_DIR)/* $(MAIN_EXEC) $(TESTS_EXEC)


MKDIR_P ?= mkdir -p