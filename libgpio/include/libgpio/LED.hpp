#ifndef LIBGPIO_LED
#define LIBGPIO_LED

#include <libgpio/internal/Device.hpp>

namespace libgpio
{
    
class LED : public Device
{
public:
    LED(uint32_t gpioPin);
    ~LED() = default;

    /// @brief Set the output of the LED
    /// @param value true = On, false = Off
    void setOutput(bool value);

private:
    unsigned int m_gpioPin;
};

} // namespace libgpio

#endif // LIBGPIO_LED
