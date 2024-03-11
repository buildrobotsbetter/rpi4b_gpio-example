
add_executable(flash-led ${CMAKE_CURRENT_LIST_DIR}/flash-led.cpp)
target_link_libraries(flash-led PUBLIC pigpio fmt)

add_executable(flash-led1 ${CMAKE_CURRENT_LIST_DIR}/flash-led1.cpp)
target_link_libraries(flash-led1 PUBLIC pigpio fmt)

add_executable(flash-led2 ${CMAKE_CURRENT_LIST_DIR}/flash-led2.cpp)
target_link_libraries(flash-led2 PUBLIC pigpio fmt)

add_executable(flash-led3 ${CMAKE_CURRENT_LIST_DIR}/flash-led3.cpp)
target_link_libraries(flash-led3 PUBLIC pigpio fmt)


# All executables after this point needs the libgpio library

add_executable(flash-led4 ${CMAKE_CURRENT_LIST_DIR}/flash-led4.cpp)
target_link_libraries(flash-led4 PUBLIC libgpio)
