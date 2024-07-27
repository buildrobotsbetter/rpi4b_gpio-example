#ifndef LIBGPIO_DIGITALOUTPUT
#define LIBGPIO_DIGITALOUTPUT

#if defined(LIBGPIO_USE_PIGPIO)

#include "./pigpio/DigitalOutput.hpp"
namespace libgpio {
    using DigitalOutput = _libgpio::pigpio::DigitalOutput;
}

#elif defined(LIBGPIO_USE_PIGPIOD_IF2)

#include "./pigpiod_if2/DigitalOutput.hpp"
namespace libgpio {
    using DigitalOutput = _libgpio::pigpiod_if2::DigitalOutput;
}

#else

#error "No GPIO library specified"

#endif

#endif // LIBGPIO_DIGITALOUTPUT
