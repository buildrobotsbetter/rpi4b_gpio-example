set(COMMON_SOURCES
	./include/libgpio/Device.hpp
	./include/libgpio/DigitalOutput.hpp
	./include/libgpio/I2C.hpp
	./include/libgpio/LED.hpp
	./include/libgpio/MotorDirection.hpp
	./include/libgpio/MotorDriver.hpp
	./include/libgpio/PullDirection.hpp
	./include/libgpio/Switch.hpp
	./include/libgpio/Utilities.hpp
	./src/libgpio/MotorDirection.cpp
	./src/libgpio/PullDirection.cpp
)

set(PIGPIO_SOURCES
	./include/libgpio/pigpio/Device.hpp
	./include/libgpio/pigpio/DigitalOutput.hpp
	./include/libgpio/pigpio/I2C.hpp
	./include/libgpio/pigpio/MotorDriver.hpp
	./include/libgpio/pigpio/PullDirectionEnum.hpp
	./include/libgpio/pigpio/Switch.hpp
	./src/libgpio/pigpio/Device.cpp
	./src/libgpio/pigpio/DigitalOutput.cpp
	./src/libgpio/pigpio/I2C.cpp
	./src/libgpio/pigpio/MotorDriver.cpp
	./src/libgpio/pigpio/Switch.cpp
)

set(PIGPIOD_IF2_SOURCES
	./include/libgpio/pigpiod_if2/Device.hpp
	./include/libgpio/pigpiod_if2/DigitalOutput.hpp
	./include/libgpio/pigpiod_if2/I2C.hpp
	./include/libgpio/pigpiod_if2/MotorDriver.hpp
	./include/libgpio/pigpiod_if2/PullDirectionEnum.hpp
	./include/libgpio/pigpiod_if2/Switch.hpp
	./src/libgpio/pigpiod_if2/Device.cpp
	./src/libgpio/pigpiod_if2/DigitalOutput.cpp
	./src/libgpio/pigpiod_if2/I2C.cpp
	./src/libgpio/pigpiod_if2/MotorDriver.cpp
	./src/libgpio/pigpiod_if2/Switch.cpp
)

