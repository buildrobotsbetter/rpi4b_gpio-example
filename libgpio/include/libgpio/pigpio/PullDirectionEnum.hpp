#ifndef LIBGPIO_PIGPIO_PULLDIRECTION
#define LIBGPIO_PIGPIO_PULLDIRECTION

#include <pigpio.h>

namespace _libgpio
{
namespace pigpio
{
namespace PullDirection
{
    
enum Value
{ 
    OFF = PI_PUD_OFF,
    DOWN = PI_PUD_DOWN,
    UP = PI_PUD_UP
};

} // namespace PullDirection
} // namespace pigpio
} // namespace _libgpio

#endif // LIBGPIO_PIGPIO_PULLDIRECTION
