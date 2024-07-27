#ifndef LIBGPIO_DEVICE_H
#define LIBGPIO_DEVICE_H

#if defined(LIBGPIO_USE_PIGPIO)

#include "./pigpio/Device.hpp"
namespace libgpio {
    using Device = _libgpio::pigpio::Device;
}

#elif defined(LIBGPIO_USE_PIGPIOD_IF2)

#include "./pigpiod_if2/Device.hpp"
namespace libgpio {
    using Device = _libgpio::pigpiod_if2::Device;
}

#else

#error "No GPIO library specified"

#endif

#endif // LIBGPIO_DEVICE_H
