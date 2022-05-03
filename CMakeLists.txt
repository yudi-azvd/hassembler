cmake_minimum_required(VERSION 3.5)

project(hassembler)

# Output colorido para Ninja
# https://medium.com/@alasher/colored-c-compiler-output-with-ninja-clang-gcc-10bfe7f2b949
# https://github.com/ninja-build/ninja/issues/174
# option(FORCE_COLORED_OUTPUT "Always produce ANSI-colored output (GNU/Clang only)" TRUE)
if(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
  add_compile_options(-fdiagnostics-color=always)
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
  add_compile_options(-fcolor-diagnostics)
endif()


set(CMAKE_CXX_FLAGS "-Wall -Wextra -ansi -pedantic -std=c++11")

include_directories(
  src
  src/hasm
  lib/doctest
)


add_library(hasm_lib STATIC
  src/hasm/hasm.cpp
  src/hasm/hasmdata.cpp
  src/hasm/hasmparametersparser.cpp
  )
target_include_directories(hasm_lib PUBLIC
  ${PROJECT_SOURCE_DIR}/src/hasm/hasm)

add_library(input STATIC
  src/hasm/input/input.cpp)
target_include_directories(input PUBLIC
  ${PROJECT_SOURCE_DIR}/src/hasm/input)


add_library(assembler STATIC
  src/hasm/assembler/assemblydata.cpp
  src/hasm/assembler/oldassembler.cpp
  src/hasm/assembler/source.cpp
  src/hasm/assembler/line.cpp
  src/hasm/assembler/twopasses/twopassesassembler.cpp
  src/hasm/assembler/twopasses/zerothpass.cpp
  src/hasm/assembler/twopasses/zerothpass2.cpp
  src/hasm/assembler/twopasses/firstpass.cpp
  src/hasm/assembler/parser/parser.cpp
  src/hasm/assembler/scanner/scanner.cpp
  src/hasm/assembler/instructions/instructionscontainer.cpp
  )
target_include_directories(assembler PUBLIC
  ${PROJECT_SOURCE_DIR}/src/assembler
  ${PROJECT_SOURCE_DIR}/src/hasm/assembler/twopasses
  ${PROJECT_SOURCE_DIR}/src/hasm/assembler/parser
  ${PROJECT_SOURCE_DIR}/src/hasm/assembler/scanner
  ${PROJECT_SOURCE_DIR}/src/hasm/assembler/instructions
  )


add_library(linker STATIC
  src/hasm/linker/linker.cpp)
target_include_directories(input PUBLIC
  ${PROJECT_SOURCE_DIR}/src/hasm/input)


add_library(util STATIC
  src/hasm/util/util.cpp
  src/hasm/util/correctionfactortable.cpp
  src/hasm/util/definitionstable.cpp
  src/hasm/util/usagetable.cpp
  src/hasm/util/symbolstable.cpp
  )
target_include_directories(util PUBLIC
  ${PROJECT_SOURCE_DIR}/src/hasm/util)

# file(GLOB srcs_input "src/hasm/input/*.cpp")
# file(GLOB srcs_assembler "src/hasm/assembler/*.cpp" "src/hasm/assembler/twopasses/*.cpp" "src/hasm/assembler/scanner/*.cpp" )
# file(GLOB srcs_linker "src/hasm/linker/*.cpp")
# file(GLOB srcs_util "src/hasm/util/*.cpp")


file(GLOB srcs_hasm "src/hasm/*.cpp")
add_executable(hasm "src/main.cpp" ${srcs_hasm})
target_link_libraries(hasm PRIVATE input assembler linker util)


###################
# Testes Unitários
###################
file(GLOB srcs_utests
  "src/hasm/_tests/*.ut.cpp"
  "src/hasm/assembler/_tests/*.ut.cpp"
    "src/hasm/assembler/twopasses/_tests/*.ut.cpp"
    "src/hasm/assembler/scanner/_tests/*.ut.cpp"
    "src/hasm/assembler/parser/_tests/*.ut.cpp"
    "src/hasm/assembler/instructions/_tests/*.ut.cpp"
  "src/hasm/linker/_tests/*.ut.cpp"
  "src/hasm/util/_tests/*.ut.cpp")
add_executable(utests
  "src/main.ut.cpp"
  # ${srcs_hasm}
  # ${srcs_assembler}
  # ${srcs_linker}
  # ${srcs_util}
  ${srcs_utests}
  )
target_link_libraries(utests PRIVATE assembler linker util hasm_lib)
