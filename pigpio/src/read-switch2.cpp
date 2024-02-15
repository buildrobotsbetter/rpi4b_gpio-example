#include <libgpio/Switch.hpp>

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
    // DIP Switch is connected to GPIO17 (physical pin 11)
    static unsigned int SWITCH_GPIO_PIN = 17; 

    signal(SIGINT, signalHandler);

    // Print the pigpio library version
    std::cout << "Using pigpio version " << gpioVersion() << std::endl;
    std::cout << "Running on " << fmt::format("{:x}", gpioHardwareRevision()) << std::endl;

    std::cout << "Configuring Switch on " << SWITCH_GPIO_PIN << std::endl;
    auto switch1 = libgpio::Switch(SWITCH_GPIO_PIN, libgpio::PullDirection::UP);

    bool switchState = false;
    isRunning = true;
    while (isRunning)
    {
        // Negative logic, ON = False, OFF = True
        bool isActive = switch1.getInput();
        bool newSwitchState = isActive;

        if (switchState != newSwitchState)
        {
            switchState = newSwitchState;
            std::cout << "State = " << (newSwitchState ? "Active" : "NOT Active") << std::endl;   
        }
    }

    return 0;    
}
