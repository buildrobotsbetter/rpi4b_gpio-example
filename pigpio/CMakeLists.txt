cmake_minimum_required(VERSION 3.18 FATAL_ERROR)

project(gpio-example)
set(CMAKE_CXX_STANDARD 11)

# Build the libgpio library
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../libgpio libgpio)

# Build executables
add_subdirectory(src/flash-led)
add_subdirectory(src/use-signalhandler)
add_subdirectory(src/read-switch)
add_subdirectory(src/motor-controller)
add_subdirectory(src/i2c-accelerometer)
