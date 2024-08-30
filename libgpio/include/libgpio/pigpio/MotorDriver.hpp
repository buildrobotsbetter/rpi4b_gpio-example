#ifndef LIBGPIO_PIGPIO_MOTORDRIVER
#define LIBGPIO_PIGPIO_MOTORDRIVER

#include <libgpio/pigpio/Device.hpp>
#include <libgpio/pigpio/DigitalOutput.hpp>
#include <libgpio/MotorDirection.hpp>

namespace _libgpio
{
namespace pigpio
{
    
class MotorDriver : public Device
{
public:
    /// @brief Construct a MotorDriver object
    /// @param input1Pin the GPIO number of the pin connected to the 'IN1' pin on the MotorDriver
    /// @param input2Pin the GPIO number of the pin connected to the 'IN2' pin on the MotorDriver
    /// @param enablePin the GPIO number of the pin connected to the 'EN' pin on the MotorDriver
    MotorDriver(uint32_t input1Pin, uint32_t input2Pin, uint32_t enablePin);
    ~MotorDriver() override;

    /// @brief Get the current direction of the motor
    /// @return the MotorDirection enumeration indicating the motor direction
    const libgpio::MotorDirection& getDirection() const;

    /// @brief Set the direction of the motor
    // When set to FORWARD, input1Pin is set to HIGH, and input2Pin is set to LOW
    // When set to BACKWARD, input1Pin is set to LOW, and input2Pin is set to HIGH
    void setDirection(const libgpio::MotorDirection& value);
   
    /// @brief Retrieve the last commanded effort
    /// @param value the effort percent [0.0, 100.0]
    double getEffort_percent() const;
    
    /// @brief Set the effort at which to drive the motor
    /// Effort is a percentage of the maximum such that 0% effort = stopped, 100% effort = maximum
    /// @param value the desired effort percent [0.0, 100.0]
    void setEffort_percent(double value);

private:
    DigitalOutput m_input1Pin;
    DigitalOutput m_input2Pin;
    unsigned int m_enablePin;
    libgpio::MotorDirection m_direction;
    double m_effort_percent;
};

} // namespace pigpio
} // namespace _libgpio

#endif // LIBGPIO_PIGPIO_MOTORDRIVER
