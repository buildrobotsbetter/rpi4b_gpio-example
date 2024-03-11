
add_executable(use-signalhandler1 ${CMAKE_CURRENT_LIST_DIR}/use-signalhandler1.cpp)
target_link_libraries(use-signalhandler1 PUBLIC pigpio fmt)

add_executable(use-signalhandler2 ${CMAKE_CURRENT_LIST_DIR}/use-signalhandler2.cpp)
target_link_libraries(use-signalhandler2 PUBLIC pigpio fmt)

add_executable(use-signalhandler3 ${CMAKE_CURRENT_LIST_DIR}/use-signalhandler3.cpp)
target_link_libraries(use-signalhandler3 PUBLIC pigpio fmt)

# All executables after this point needs the libgpio library

