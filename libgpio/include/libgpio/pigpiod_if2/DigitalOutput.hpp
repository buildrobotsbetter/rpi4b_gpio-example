#ifndef LIBGPIO_PIGPIOD_IF2_DIGITALOUTPUT
#define LIBGPIO_PIGPIOD_IF2_DIGITALOUTPUT

#include <libgpio/pigpiod_if2/Device.hpp>

namespace _libgpio::pigpiod_if2
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

} // namespace _libgpio::pigpigpiod_if2pio

#endif // LIBGPIO_PIGPIOD_IF2_DIGITALOUTPUT