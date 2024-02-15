#include <libgpio/LED.hpp>

#include <stdexcept>
#include <fmt/core.h>

namespace libgpio
{

LED::LED(uint32_t gpioPin):
    m_gpioPin(gpioPin)
{
    auto result = gpioSetMode(m_gpioPin, PI_OUTPUT);
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

void LED::setOutput(bool value)
{
    gpioWrite(m_gpioPin, static_cast<unsigned int>(value));
}

} // namespace libgpio
