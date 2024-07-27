cmake_minimum_required(VERSION 3.18 FATAL_ERROR)

project(libgpio VERSION 0.2.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)

include(${CMAKE_CURRENT_LIST_DIR}/sources.cmake)

if(DEFINED LIBGPIO_USE_PIGPIOD_IF2)
    message(NOTICE "Using pigpiod_if2 library")
    set(SOURCES ${COMMON_SOURCES} ${PIGPIOD_IF2_SOURCES})
    set(GPIO_LIBRARY pigpiod_if2)
    set(GPIO_LIBRARY_DEFINE LIBGPIO_USE_PIGPIOD_IF2)
else()
    message(NOTICE "Using pigpio library")
    set(SOURCES ${COMMON_SOURCES} ${PIGPIO_SOURCES})
    set(GPIO_LIBRARY pigpio)
    set(GPIO_LIBRARY_DEFINE LIBGPIO_USE_PIGPIO)
endif()

set(LIBGPIO_VERSION ${CMAKE_PROJECT_VERSION})
set(LIBGPIO_LIBRARY "${GPIO_LIBRARY}")

add_library(libgpio ${SOURCES})
target_include_directories(libgpio PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
)
target_compile_definitions(libgpio 
    PUBLIC 
        ${GPIO_LIBRARY_DEFINE}
        LIBGPIO_VERSION="${LIBGPIO_VERSION}"
        LIBGPIO_LIBRARY="${LIBGPIO_LIBRARY}"
) 
target_link_libraries(libgpio PUBLIC ${GPIO_LIBRARY} fmt)
