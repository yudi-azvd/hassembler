# Usando file GLOB: não tão moderno assim
file(GLOB srcs_linker "*.cpp")
add_library(Linker ${srcs_linker})