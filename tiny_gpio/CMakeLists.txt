cmake_minimum_required(VERSION 3.18 FATAL_ERROR)

project(flash-led-example C CXX)
set(CMAKE_CXX_STANDARD 11)

add_executable(flash-led src/tiny_gpio.c src/flash-led.cpp)
target_link_libraries(flash-led PUBLIC fmt)

add_executable(flash-led2 src/tiny_gpio.c src/flash-led2.cpp)
target_link_libraries(flash-led2 PUBLIC fmt)

add_executable(flash-led3 src/tiny_gpio.c src/flash-led3.cpp)
target_link_libraries(flash-led3 PUBLIC fmt)
