#ifndef LIBGPIO_PIGPIOD_IF2_PULLDIRECTION
#define LIBGPIO_PIGPIOD_IF2_PULLDIRECTION

#include <pigpiod_if2.h>

namespace _libgpio
{
namespace pigpiod_if2
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
} // namespace pigpiod_if2
} // namespace _libgpio

#endif // LIBGPIO_PIGPIOD_IF2_PULLDIRECTION
