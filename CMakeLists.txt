cmake_minimum_required(VERSION 3.13)
project(main_bom)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin/)

include_directories(inc)


add_executable(main_bom src/main.cpp src/Peripherals/Gpio.cpp inc/Peripherals/Gpio.h inc/Config.h src/AssembleConnection.cpp inc/AssembleConnection.h src/Bom.cpp inc/Bom.h src/Peripherals/Display.cpp inc/Peripherals/Display.h src/Peripherals/Keypad.cpp inc/Peripherals/Keypad.h src/Fuses.cpp inc/Fuses.h)
target_link_libraries( main_bom pthread )