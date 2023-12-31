#include <pigpiod_if2.h>
#include <iostream>
#include <fmt/core.h> // For improved string formatting
#include <chrono>
#include <thread>


int main()
{
    // LED is connected to GPIO26 (physical pin 37)
    static const unsigned int LED_GPIO_PIN = 26; 

    // Connect to the local pigpio daemon
    std::cout << "Connecting to pigpio daemon... ";
    int gpioHandle = pigpio_start(nullptr, nullptr);
    if (gpioHandle < 0)
    {
        std::cout << "ERROR" << std::endl;
        std::cout << "Returned Error = " << gpioHandle << std::endl;
        return -1;    
    }
    std::cout << "SUCCESS" << std::endl;

    // Print the pigpio library version
    std::cout << "Using pigpio version " << get_pigpio_version(gpioHandle) << std::endl;
    std::cout << "Running on " << fmt::format("{:x}", get_hardware_revision(gpioHandle)) << std::endl;

    std::cout << "Configuring LED on " << LED_GPIO_PIN << std::endl;

    int gpioResult = 0;

    // Configure the GPIO pin attached to the LED as a output pin
    // PI_OUTPUT is defined within the pigpio library
    gpioResult = set_mode(gpioHandle, LED_GPIO_PIN, PI_OUTPUT);

    // Check the result to ensure the GPIO pin could be properly configured
    if (gpioResult != 0) // A value of 0 = OK
    {
        switch (gpioResult)
        {
            case PI_BAD_GPIO:
            {
                std::cout << LED_GPIO_PIN << "is a bad gpio pin" << std::endl;
                return -1;
            }

            case PI_BAD_MODE:
            {
                std::cout << "Bad mode specified for gpio pin " << LED_GPIO_PIN << std::endl;
                return -1; 
            }

            default:
            {
                std::cout << "Unexpected error encountered when setting mode specified for gpio pin " << LED_GPIO_PIN << std::endl;
                std::cout << "Result = " << gpioResult << std::endl;
                return -1;
            }
        }
    }

    while (true)
    {
        gpio_write(gpioHandle, LED_GPIO_PIN, PI_ON);
        std::this_thread::sleep_for(std::chrono::seconds(1));

        gpio_write(gpioHandle, LED_GPIO_PIN, PI_OFF);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    // Close the connection to the pigpio daemon
    pigpio_stop(gpioHandle);

    return 0;    
}