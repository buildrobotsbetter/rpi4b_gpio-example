#include <pigpio.h>
#include <iostream>
#include <fmt/core.h> // For improved string formatting
#include <chrono>
#include <thread>


int main()
{
    // LED is connected to GPIO26 (physical pin 37)
    static unsigned int LED_GPIO_PIN = 26; 

    int gpioResult = 0;

    // Print the pigpio library version
    std::cout << "Using pigpio version " << gpioVersion() << std::endl;
    std::cout << "Running on " << fmt::format("{:x}", gpioHardwareRevision()) << std::endl;

    // Initialize the pigpio library
    std::cout << "Initializing pigpio... ";
    gpioResult = gpioInitialise();
    if (gpioResult == PI_INIT_FAILED)
    {
        std::cout << "ERROR" << std::endl;
        std::cout << "Error value = " << gpioResult << std::endl;
        return -1;    
    }
    std::cout << "SUCCESS" << std::endl;

    std::cout << "Configuring LED on " << LED_GPIO_PIN << std::endl;

    // Configure the GPIO pin attached to the LED as a output pin
    // PI_OUTPUT is defined within the pigpio library
    gpioResult = gpioSetMode(LED_GPIO_PIN, PI_OUTPUT);

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
        gpioWrite(LED_GPIO_PIN, PI_ON);
        std::this_thread::sleep_for(std::chrono::milliseconds(300));

        gpioWrite(LED_GPIO_PIN, PI_OFF);
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }

    // Terminate the pigpio library to clean up
    gpioTerminate();

    return 0;    
}