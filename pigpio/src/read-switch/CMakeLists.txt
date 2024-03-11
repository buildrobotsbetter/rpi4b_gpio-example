
add_executable(read-switch ${CMAKE_CURRENT_LIST_DIR}/read-switch.cpp)
target_link_libraries(read-switch PUBLIC pigpio fmt)

# All executables after this point needs the libgpio library

add_executable(read-switch1 ${CMAKE_CURRENT_LIST_DIR}/read-switch1.cpp)
target_link_libraries(read-switch1 PUBLIC libgpio)

add_executable(read-switch2 ${CMAKE_CURRENT_LIST_DIR}/read-switch2.cpp)
target_link_libraries(read-switch2 PUBLIC libgpio)

add_executable(read-switch3 ${CMAKE_CURRENT_LIST_DIR}/read-switch3.cpp)
target_link_libraries(read-switch3 PUBLIC libgpio)
