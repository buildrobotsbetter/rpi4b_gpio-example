cmake_minimum_required(VERSION 3.18 FATAL_ERROR)

project(libgpio VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)

include(${CMAKE_CURRENT_LIST_DIR}/sources.cmake)

add_library(libgpio ${SOURCES})
target_include_directories(libgpio PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
)
target_link_libraries(libgpio PUBLIC pigpio fmt)
