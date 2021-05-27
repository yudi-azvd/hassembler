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
  lib
)

file(GLOB srcs_hasm "src/hasm/*.cpp")
file(GLOB srcs_assembler "src/assembler/*.cpp")
file(GLOB srcs_linker "src/linker/*.cpp")
file(GLOB srcs_util "src/util/*.cpp")

add_executable(hasm "src/main.cpp"
  ${srcs_hasm}
  ${srcs_assembler}
  ${srcs_linker}
  ${srcs_util})

file(GLOB srcs_utests
  "src/hasm/_tests/*.ut.cpp"
  "src/assembler/_tests/*.ut.cpp"
  "src/linker/_tests/*.ut.cpp"
  "src/util/_tests/*.ut.cpp")
add_executable(utests
  ${srcs_hasm}
  ${srcs_assembler}
  ${srcs_linker}
  ${srcs_util}
  ${srcs_utests}
  "src/main.ut.cpp")
