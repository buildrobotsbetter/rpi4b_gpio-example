cmake_minimum_required(VERSION 3.18 FATAL_ERROR)

project(flash-led-example)
set(CMAKE_CXX_STANDARD 11)

add_executable(flash-led src/flash-led.cpp)
target_link_libraries(flash-led PUBLIC pigpio fmt)

add_executable(flash-led1 src/flash-led1.cpp)
target_link_libraries(flash-led1 PUBLIC pigpio fmt)

add_executable(flash-led2 src/flash-led2.cpp)
target_link_libraries(flash-led2 PUBLIC pigpio fmt)

add_executable(flash-led3 src/flash-led3.cpp)
target_link_libraries(flash-led3 PUBLIC pigpio fmt)