#ifndef LIBGPIO_PIGPIO_DEVICE_H
#define LIBGPIO_PIGPIO_DEVICE_H

#include <pigpio.h>

namespace _libgpio::pigpio
{

class Device
{
public:
    Device();
    virtual ~Device();

private:
    static uint64_t m_deviceCount;
};

} // namespace _libgpio::pigpio

#endif // LIBGPIO_PIGPIO_DEVICE_H
