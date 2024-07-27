#ifndef LIBGPIO_I2C
#define LIBGPIO_I2C

#if defined(LIBGPIO_USE_PIGPIO)

#include "./pigpio/I2C.hpp"
namespace libgpio {
    using I2C = _libgpio::pigpio::I2C;
}

#elif defined(LIBGPIO_USE_PIGPIOD_IF2)

#include "./pigpiod_if2/I2C.hpp"
namespace libgpio {
    using I2C = _libgpio::pigpiod_if2::I2C;
}

#else

#error "No GPIO library specified"

#endif

#endif // LIBGPIO_I2CBUS
