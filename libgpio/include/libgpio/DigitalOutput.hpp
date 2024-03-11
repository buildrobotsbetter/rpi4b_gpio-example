#ifndef LIBGPIO_DIGITALOUTPUT
#define LIBGPIO_DIGITALOUTPUT

#include <libgpio/Device.hpp>

namespace libgpio
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

} // namespace libgpio

#endif // LIBGPIO_DIGITALOUTPUT
