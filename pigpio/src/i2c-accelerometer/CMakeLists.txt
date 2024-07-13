
add_executable(i2c-accelerometer ${CMAKE_CURRENT_LIST_DIR}/i2c-accelerometer.cpp)
target_link_libraries(i2c-accelerometer PUBLIC pigpio fmt)

add_executable(i2c-accelerometer2 ${CMAKE_CURRENT_LIST_DIR}/i2c-accelerometer2.cpp)
target_link_libraries(i2c-accelerometer2 PUBLIC pigpio fmt)

add_executable(i2c-accelerometer3 ${CMAKE_CURRENT_LIST_DIR}/i2c-accelerometer3.cpp)
target_link_libraries(i2c-accelerometer3 PUBLIC pigpio fmt)

# All executables after this point needs the libgpio library

add_executable(i2c-accelerometer4 ${CMAKE_CURRENT_LIST_DIR}/i2c-accelerometer4.cpp)
target_link_libraries(i2c-accelerometer4 PUBLIC libgpio)

add_executable(i2c-accelerometer5 ${CMAKE_CURRENT_LIST_DIR}/i2c-accelerometer5.cpp)
target_link_libraries(i2c-accelerometer5 PUBLIC libgpio)
