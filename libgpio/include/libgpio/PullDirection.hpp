#ifndef LIBGPIO_PULLDIRECTION
#define LIBGPIO_PULLDIRECTION

#include <string>

#if defined(LIBGPIO_USE_PIGPIO)

#include "./pigpio/PullDirectionEnum.hpp"
namespace _libgpio {
    namespace PullDirection = _libgpio::pigpio::PullDirection;
}

#elif defined(LIBGPIO_USE_PIGPIOD_IF2)

#include "./pigpiod_if2/PullDirectionEnum.hpp"
namespace _libgpio {
    namespace PullDirection = _libgpio::pigpiod_if2::PullDirection;
}

#else

#error "No GPIO library specified"

#endif

namespace libgpio
{
    
class PullDirection
{
public:
    // Enum values match the pigpio PI_PUD_xxx define values
    // to allow straight pass through to pigpio functions
    enum Value {
        OFF = _libgpio::PullDirection::OFF,
        DOWN = _libgpio::PullDirection::DOWN,
        UP = _libgpio::PullDirection::UP
    };

    constexpr PullDirection(uint8_t value) :
        PullDirection((PullDirection::Value)value) {}
    constexpr PullDirection(Value value) :
        value(value) {};
    ~PullDirection() = default;

    operator Value() const;            // Allow switch and comparisons.
    explicit operator bool() = delete; // Prevent usage: if (status)

    std::string toString() const;

private:
    Value value;
};

} // namespace libgpio

#endif // LIBGPIO_PULLDIRECTION
