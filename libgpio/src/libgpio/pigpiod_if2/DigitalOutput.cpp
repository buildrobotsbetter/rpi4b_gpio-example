#include <libgpio/pigpiod_if2/DigitalOutput.hpp>

#include <stdexcept>
#include <fmt/core.h>

namespace _libgpio
{
namespace pigpiod_if2
{

DigitalOutput::DigitalOutput(uint32_t gpioPin):
    m_gpioPin(gpioPin)
{
    auto result = set_mode(getGpioHandle(), m_gpioPin, PI_OUTPUT);
    if (result == 0)
    {
        return;
    }

    switch (result)
    {       
        case PI_BAD_GPIO:
        {
            throw std::invalid_argument(fmt::format("{} is a bad gpio pin", m_gpioPin));
        }

        case PI_BAD_MODE:
        {
            throw std::runtime_error(fmt::format("Bad mode specified for gpio pin {}", m_gpioPin));
        }

        default:
        {
            throw std::runtime_error(fmt::format("Unexpected error encountered when setting mode specified for gpio pin {} (Error = {})", m_gpioPin, result));
        }
    }
}

DigitalOutput::~DigitalOutput()
{
    // Automatically turn off on destruction
    setOutput(false);
}

void DigitalOutput::setOutput(bool value)
{
    auto result = gpio_write(getGpioHandle(), m_gpioPin, static_cast<unsigned int>(value));
    if (result == 0)
    {
        return;
    }

    switch (result)
    {       
        case PI_BAD_GPIO:
        {
            throw std::runtime_error(fmt::format("{} is a bad gpio pin", m_gpioPin));
        }

        case PI_BAD_LEVEL:
        {
            throw std::runtime_error(fmt::format("Bad level specified for gpio pin {}", m_gpioPin));
        }

        default:
        {
            throw std::runtime_error(fmt::format("Unexpected error encountered when setting mode specified for gpio pin {} (Error = {})", m_gpioPin, result));
        }
    }
}

} // namespace pigpiod_if2
} // namespace _libgpio
