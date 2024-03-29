#ifndef LIBGPIO_LED
#define LIBGPIO_LED

#include <libgpio/Device.hpp>
#include <libgpio/PullDirection.hpp>

namespace libgpio
{
    
class Switch : public Device
{
public:
    Switch(uint32_t gpioPin, PullDirection pullDirection);
    ~Switch() = default;

    /// @brief Get the input generated by the switch
    /// @param value true = HIGH, false = LOW
    bool getInput() const;

private:
    void configurePull();
    void configureMode();

    uint32_t m_gpioPin;
    PullDirection m_pullDirection;
};

} // namespace libgpio

#endif // LIBGPIO_LED
