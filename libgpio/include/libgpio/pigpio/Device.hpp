#ifndef LIBGPIO_PIGPIO_DEVICE_H
#define LIBGPIO_PIGPIO_DEVICE_H

#include <pigpio.h>

namespace _libgpio
{
namespace pigpio
{

class Device
{
public:
    Device();
    virtual ~Device();

private:
    static uint64_t m_deviceCount;
};

} // namespace pigpio
} // namespace _libgpio

#endif // LIBGPIO_PIGPIO_DEVICE_H
