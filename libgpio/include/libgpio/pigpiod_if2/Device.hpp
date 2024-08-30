#ifndef LIBGPIO_PIGPIOD_IF2_DEVICE_H
#define LIBGPIO_PIGPIOD_IF2_DEVICE_H

#include <pigpiod_if2.h>

namespace _libgpio
{
namespace pigpiod_if2
{

class Device
{
public:
    Device();
    virtual ~Device();

protected:
    int getGpioHandle() const;

private:
    static uint64_t m_deviceCount;
    static int m_gpioHandle;
};

} // namespace pigpiod_if2
} // namespace _libgpio

#endif // LIBGPIO_PIGPIOD_IF2_DEVICE_H
