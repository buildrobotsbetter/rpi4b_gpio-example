
add_executable(motor-controller ${CMAKE_CURRENT_LIST_DIR}/motor-controller.cpp)
target_link_libraries(motor-controller PUBLIC pigpio fmt)

# All executables after this point needs the libgpio library

add_executable(motor-controller2 ${CMAKE_CURRENT_LIST_DIR}/motor-controller2.cpp)
target_link_libraries(motor-controller2 PUBLIC libgpio)

add_executable(motor-controller3 ${CMAKE_CURRENT_LIST_DIR}/motor-controller3.cpp)
target_link_libraries(motor-controller3 PUBLIC libgpio)

add_executable(motor-controller4 ${CMAKE_CURRENT_LIST_DIR}/motor-controller4.cpp)
target_link_libraries(motor-controller4 PUBLIC libgpio)
