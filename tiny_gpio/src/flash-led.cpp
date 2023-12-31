#include "tiny_gpio.h"
#include <iostream>
#include <fmt/core.h>
#include <chrono>
#include <thread>

int main()
{
    // LED is connected to GPIO26 (physical pin 37)
    static unsigned int LED_GPIO_PIN = 26; 

    // Print the pigpio library version
    std::cout << "Using tiny_gpio" << std::endl;
    std::cout << "Running on " << fmt::format("{:x}", gpioHardwareRevision()) << std::endl;

    int gpioResult = 0;

    std::cout << "Initializing tiny_gpio... ";
    gpioResult = gpioInitialise();
    if (gpioResult < 0)
    {
        std::cout << "ERROR" << std::endl;
        std::cout << "Error value = " << gpioResult << std::endl;
        return -1;    
    }
    std::cout << "SUCCESS" << std::endl;

    std::cout << "Configuring LED on " << LED_GPIO_PIN << std::endl;

    // Configure the GPIO pin attached to the LED as a output pin
    // PI_OUTPUT is defined within the pigpio library
    gpioSetMode(LED_GPIO_PIN, PI_OUTPUT);

    while (true)
    {
        gpioWrite(LED_GPIO_PIN, 1);
        std::this_thread::sleep_for(std::chrono::seconds(1));

        gpioWrite(LED_GPIO_PIN, 0);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}