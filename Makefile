
EXEC_ASSEMBLER ?= montador
EXEC_LINKER ?= ligador
EXEC_SIMULATOR ?= simulador

EXEC_TESTS ?= utests

CXX = g++

CXXFLAGS = -g -Wall -Wpedantic

BUILD_DIR ?= build
SRC_DIR ?= src

MAIN_ASSEMBLER := $(SRC_DIR)/$(EXEC_ASSEMBLER)/$(EXEC_ASSEMBLER).cpp
SRCS_ASSEMBLER := $(wildcard $(SRC_DIR)/$(EXEC_ASSEMBLER)/*.cpp)
OBJS_ASSEMBLER := $(SRCS_ASSEMBLER:%=$(BUILD_DIR)/m/%.o) # REPARE O 'm' !!!

MAIN_LINKER := $(SRC_DIR)/$(EXEC_LINKER)/$(EXEC_LINKER).cpp
SRCS_LINKER := $(wildcard $(SRC_DIR)/$(EXEC_LINKER)/*.cpp)
OBJS_LINKER := $(SRCS_LINKER:%=$(BUILD_DIR)/l/%.o) # REPARE O 'l' !!!

MAIN_SIMULATOR := $(SRC_DIR)/$(EXEC_SIMULATOR)/$(EXEC_SIMULATOR).cpp
SRCS_SIMULATOR := $(wildcard $(SRC_DIR)/$(EXEC_SIMULATOR)/*.cpp)
OBJS_SIMULATOR := $(SRCS_SIMULATOR:%=$(BUILD_DIR)/s/%.o) # REPARE O 's' !!!
# Existe alguma maneira mais concisa de fazer o que está na linha debaixo?
TEST_SRCS := $(wildcard tests/*.test.cpp) $(wildcard tests/**/*.test.cpp)
TEST_OBJS := $(filter-out build/m/src/$(EXEC_ASSEMBLER)/$(EXEC_ASSEMBLER).cpp.o, $(OBJS_ASSEMBLER)) \
						 $(filter-out build/l/src/$(EXEC_LINKER)/$(EXEC_LINKER).cpp.o, $(OBJS_LINKER)) \
						 $(TEST_SRCS:%=$(BUILD_DIR)/%.o)

all: assembler simulator linker

everything: all utests


####################################
# Executável MONTADOR              #
####################################
assembler: $(BUILD_DIR)/$(EXEC_ASSEMBLER) 
	@echo " > assembler: Done $@ => $<"
	@cp $< $(EXEC_ASSEMBLER)
	@echo " ------------------------"

$(BUILD_DIR)/$(EXEC_ASSEMBLER): $(OBJS_ASSEMBLER) $(MAIN_ASSEMBLER)
	@echo ">> assembler: Building executable"
	@$(CXX) $(CXXFLAGS) $(OBJS_ASSEMBLER) -o $@

$(BUILD_DIR)/m/%.cpp.o: %.cpp
	@echo ">> assembler: Building source file: $<"
	@echo " > assembler: Output file: $@\n"
	@$(MKDIR_P) $(dir $@)
	@$(CXX) $(CXXFLAGS) -c $< -o $@


####################################
# Executável LIGADOR               #
####################################
linker: $(BUILD_DIR)/$(EXEC_LINKER) 
	@echo " > linker: Done $@ => $<"
	@cp $< $(EXEC_LINKER)
	@echo " ------------------------"

$(BUILD_DIR)/$(EXEC_LINKER): $(OBJS_LINKER) $(MAIN_LINKER) $(BUILD_DIR)/m/$(SRC_DIR)/$(EXEC_ASSEMBLER)/util.cpp.o
	@echo ">> linker: Building executable"
	@$(CXX) $(CXXFLAGS) $(OBJS_LINKER) -o $@

$(BUILD_DIR)/l/%.cpp.o: %.cpp
	@echo ">> linker: Building source file: $<"
	@echo " > linker: Output file: $@\n"
	@$(MKDIR_P) $(dir $@)
	@$(CXX) $(CXXFLAGS) -c $< -o $@


####################################
# Executável SIMULADOR             #
####################################
simulator: $(BUILD_DIR)/$(EXEC_SIMULATOR)
	@echo " > simulator: Done $@ => $<"
	@cp $< $(EXEC_SIMULATOR)
	@echo " ------------------------"

$(BUILD_DIR)/$(EXEC_SIMULATOR): $(OBJS_SIMULATOR) $(MAIN_SIMULATOR)
	@echo ">> simulator: Building executable"
	@$(CXX) $(CXXFLAGS) $(OBJS_SIMULATOR) -o $@

$(BUILD_DIR)/s/%.cpp.o: %.cpp
	@echo ">> simulator: Building source file: $<"
	@echo " > simulator: Output file: $@\n"
	@$(MKDIR_P) $(dir $@)
	@$(CXX) $(CXXFLAGS) -c $< -o $@


####################################
# Executável do testes unitários	 #
####################################
utests: $(BUILD_DIR)/$(EXEC_TESTS)
	@echo " > test: Build done"
	@echo " ------------------------"

$(BUILD_DIR)/$(EXEC_TESTS): $(TEST_OBJS)
	@echo ">> test: Building TEST executable $@"
	@$(CXX) $(CXXFLAGS) $(TEST_OBJS) -o $@

$(BUILD_DIR)/%.test.cpp.o: %.test.cpp
	@echo ">> test: Building test source: $<"
	@echo " > test: Output file: $@\n"
	@$(MKDIR_P) $(dir $@)
	@$(CXX) $(CXXFLAGS) -c $< -o $@


.PHONY: clean test main

clean:
	rm -fr $(BUILD_DIR)/* $(EXEC_ASSEMBLER) $(EXEC_LINKER) $(EXEC_SIMULATOR) $(EXEC_TESTS)

remove:
	rm *.o*

MKDIR_P ?= mkdir -p