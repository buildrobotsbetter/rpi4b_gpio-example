#include <libgpio/pigpiod_if2/Device.hpp>

#include <stdexcept>
#include <fmt/core.h>

namespace _libgpio
{
namespace pigpiod_if2
{

// Initialize the static variable
uint64_t Device::m_deviceCount = 0;
int Device::m_gpioHandle = -1;


Device::Device()
{
    if (m_deviceCount == 0)
    {
        // #ifndef USE_PIGPIO_SIGNALHANDLER
        // // Disable built-in pigpio signal handling
        // // Must be called before gpioInitialise()
        // int cfg = gpioCfgGetInternals();
        // cfg |= PI_CFG_NOSIGHANDLER;
        // gpioCfgSetInternals(cfg);
        // #endif

        // Connect to the local pigpio daemon
        m_gpioHandle = pigpio_start(nullptr, nullptr);
        if (m_gpioHandle < 0 )
        {
            throw std::runtime_error(fmt::format("pigpiod_if2 initialization Failed"));
        }
    }
    m_deviceCount++;
}

Device::~Device()
{
    m_deviceCount--;
    if (m_deviceCount == 0)
    {
        pigpio_stop(m_gpioHandle);
    }
}

int Device::getGpioHandle() const
{
    return m_gpioHandle; 
}

} // namespace pigpiod_if2
} // namespace _libgpio
