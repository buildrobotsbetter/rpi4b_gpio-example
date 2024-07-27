#ifndef LIBGPIO_SWITCH
#define LIBGPIO_SWITCH

#if defined(LIBGPIO_USE_PIGPIO)

#include "./pigpio/Switch.hpp"
namespace libgpio {
    using Switch = _libgpio::pigpio::Switch;
}

#elif defined(LIBGPIO_USE_PIGPIOD_IF2)

#include "./pigpiod_if2/Switch.hpp"
namespace libgpio {
    using Switch = _libgpio::pigpiod_if2::Switch;
}

#else

#error "No GPIO library specified"

#endif

#endif // LIBGPIO_SWITCH
