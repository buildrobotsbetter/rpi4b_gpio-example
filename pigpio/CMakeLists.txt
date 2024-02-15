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


add_executable(use-signalhandler1 src/use-signalhandler1.cpp)
target_link_libraries(use-signalhandler1 PUBLIC pigpio fmt)

add_executable(use-signalhandler2 src/use-signalhandler2.cpp)
target_link_libraries(use-signalhandler2 PUBLIC pigpio fmt)

add_executable(use-signalhandler3 src/use-signalhandler3.cpp)
target_link_libraries(use-signalhandler3 PUBLIC pigpio fmt)


add_executable(read-switch src/read-switch.cpp)
target_link_libraries(read-switch PUBLIC pigpio fmt)


# Build the libgpio library
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../libgpio libgpio)

# All executables after this point needs the libgpio library
add_executable(flash-led4 src/flash-led4.cpp)
target_link_libraries(flash-led4 PUBLIC libgpio)

add_executable(read-switch1 src/read-switch1.cpp)
target_link_libraries(read-switch1 PUBLIC libgpio)

add_executable(read-switch2 src/read-switch2.cpp)
target_link_libraries(read-switch2 PUBLIC libgpio)

add_executable(read-switch3 src/read-switch3.cpp)
target_link_libraries(read-switch3 PUBLIC libgpio)
