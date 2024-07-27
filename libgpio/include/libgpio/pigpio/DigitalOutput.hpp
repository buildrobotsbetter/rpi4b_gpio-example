#ifndef LIBGPIO_PIGPIO_DIGITALOUTPUT
#define LIBGPIO_PIGPIO_DIGITALOUTPUT

#include <libgpio/pigpio/Device.hpp>

namespace _libgpio::pigpio
{

class DigitalOutput : public Device
{
public:
    DigitalOutput(uint32_t gpioPin);
    ~DigitalOutput() override;

    /// @brief Set the output of the LED
    /// @param value true = On, false = Off
    void setOutput(bool value);

private:
    unsigned int m_gpioPin;
};

} // namespace _libgpio::pigpio

#endif // LIBGPIO_PIGPIO_DIGITALOUTPUT
