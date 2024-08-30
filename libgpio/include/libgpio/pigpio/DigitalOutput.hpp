#ifndef LIBGPIO_PIGPIO_DIGITALOUTPUT
#define LIBGPIO_PIGPIO_DIGITALOUTPUT

#include <libgpio/pigpio/Device.hpp>

namespace _libgpio
{
namespace pigpio
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

} // namespace pigpio
} // namespace _libgpio

#endif // LIBGPIO_PIGPIO_DIGITALOUTPUT
