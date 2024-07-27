#include <libgpio/Switch.hpp>
#include <libgpio/Utilities.hpp>

#include <iostream>
#include <fmt/core.h> // For improved string formatting
#include <chrono>
#include <thread>
#include <signal.h>


bool isRunning = false;
void signalHandler(int signal)
{
    std::cout << "Received signal. Shutting down." << std::endl;
    isRunning = false;
}

int main()
{
    static unsigned int SWITCH_GPIO_PIN1 = 27; 
    static unsigned int SWITCH_GPIO_PIN2 = 17; 

    signal(SIGINT, signalHandler);

    // Print the pigpio library version
    // std::cout << "Using pigpio version " << gpioVersion() << std::endl;
    // std::cout << "Running on " << fmt::format("{:x}", gpioHardwareRevision()) << std::endl;
    std::cout << "Using libgpio version: " << libgpio::version() << std::endl;
    std::cout << "Using gpio library: " << libgpio::gpioLibrary() << std::endl;
    
    std::cout << "Configuring Switch on " << SWITCH_GPIO_PIN1 << std::endl;
    auto switch1 = libgpio::Switch(SWITCH_GPIO_PIN1, libgpio::PullDirection::DOWN);

    std::cout << "Configuring Switch on " << SWITCH_GPIO_PIN2 << std::endl;
    auto switch2 = libgpio::Switch(SWITCH_GPIO_PIN2, libgpio::PullDirection::UP);

    bool switchState1 = false;
    bool switchState2 = false;

    isRunning = true;
    while (isRunning)
    {
        // Positive logic, ON = True, OFF = False
        bool isActive1 = switch1.getInput();
        bool newSwitchState1 = isActive1;

        // Negative logic, ON = False, OFF = True
        bool isActive2 = switch2.getInput();
        bool newSwitchState2 = isActive2;

        if ((switchState1 != newSwitchState1) || (switchState2 != newSwitchState2))
        {
            switchState1 = newSwitchState1;
            switchState2 = newSwitchState2;

            std::cout << fmt::format("Switch 1 = {}, Switch 2 = {}", (newSwitchState1 ? "Active" : "NOT Active"), (newSwitchState2 ? "Active" : "NOT Active")) << std::endl;   
        }
    }

    return 0;    
}
