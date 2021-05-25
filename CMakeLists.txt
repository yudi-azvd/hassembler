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

add_subdirectory(src/assembler)
add_subdirectory(src/linker)


add_executable(hasm "src/main.cpp")
target_link_libraries(hasm PRIVATE Assembler)
target_link_libraries(hasm PRIVATE Linker)
target_include_directories(
  hasm PRIVATE
  "${PROJECT_BINARY_DIR}"
  "${PROJECT_SOURCE_DIR}/src/assembler"
  "${PROJECT_SOURCE_DIR}/src/linker"
)


# Usando file GLOB: não tão moderno assim
file(GLOB srcs_utests "src/**/_tests/*.ut.cpp")
add_executable(utests "src/main.ut.cpp" ${srcs_utests})
target_link_libraries(utests PRIVATE Assembler)
target_link_libraries(utests PRIVATE Linker)
target_include_directories(
  utests PRIVATE
  "${PROJECT_BINARY_DIR}"
  "${PROJECT_SOURCE_DIR}/src"
  "${PROJECT_SOURCE_DIR}/lib"
)
