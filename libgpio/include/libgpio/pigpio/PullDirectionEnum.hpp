#ifndef LIBGPIO_PIGPIO_PULLDIRECTION
#define LIBGPIO_PIGPIO_PULLDIRECTION

#include <pigpio.h>

namespace _libgpio::pigpio::PullDirection
{
    
enum Value
{ 
    OFF = PI_PUD_OFF,
    DOWN = PI_PUD_DOWN,
    UP = PI_PUD_UP
};

} // namespace _libgpio::pigpio::PullDirection

#endif // LIBGPIO_PIGPIO_PULLDIRECTION
