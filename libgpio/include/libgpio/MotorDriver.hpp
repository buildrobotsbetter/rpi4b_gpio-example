#ifndef LIBGPIO_MOTORDRIVER
#define LIBGPIO_MOTORDRIVER

#if defined(LIBGPIO_USE_PIGPIO)

#include "./pigpio/MotorDriver.hpp"
namespace libgpio {
    using MotorDriver = _libgpio::pigpio::MotorDriver;
}

#elif defined(LIBGPIO_USE_PIGPIOD_IF2)

#include "./pigpiod_if2/MotorDriver.hpp"
namespace libgpio {
    using MotorDriver = _libgpio::pigpiod_if2::MotorDriver;
}

#else

#error "No GPIO library specified"

#endif

#endif // LIBGPIO_MOTORDRIVER
