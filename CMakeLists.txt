cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(fsrstop C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(fsrstop
  fsrstop.c
)

pico_enable_stdio_usb(fsrstop 1)
pico_enable_stdio_uart(fsrstop 1)

pico_add_extra_outputs(fsrstop)

target_link_libraries(fsrstop pico_stdlib hardware_adc)

