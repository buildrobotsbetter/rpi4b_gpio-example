#include <pigpio.h>
#include <iostream>
#include <fmt/core.h> // For improved string formatting
#include <chrono>
#include <thread>


int configureGpio(int gpioPin);

int main()
{
    // LEDs are connected to GPIO26 (physical pin 37) and GPIO16 (physical pin 36)
    static unsigned int LED_GPIO_PIN1 = 26; 
    static unsigned int LED_GPIO_PIN2 = 16; 

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

    std::cout << "Configuring LED on " << LED_GPIO_PIN1 << std::endl;
    gpioResult = configureGpio(LED_GPIO_PIN1);
    if (gpioResult != 0)
    {
        return -1;
    }


    std::cout << "Configuring LED on " << LED_GPIO_PIN2 << std::endl;
    gpioResult = configureGpio(LED_GPIO_PIN2);
    if (gpioResult != 0)
    {
        return -1;
    }

    while (true)
    {
        gpioWrite(LED_GPIO_PIN1, PI_ON);
        gpioWrite(LED_GPIO_PIN2, PI_ON);
        std::this_thread::sleep_for(std::chrono::seconds(1));

        gpioWrite(LED_GPIO_PIN1, PI_OFF);
        gpioWrite(LED_GPIO_PIN2, PI_OFF);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    // Terminate the pigpio library to clean up
    gpioTerminate();

    return 0;    
}

int configureGpio(int gpioPin)
{
       // Configure the GPIO pin attached to the LED as a output pin
    // PI_OUTPUT is defined within the pigpio library
    int gpioResult = gpioSetMode(gpioPin, PI_OUTPUT);

    // Check the result to ensure the GPIO pin could be properly configured
    if (gpioResult != 0) // A value of 0 = OK
    {
        switch (gpioResult)
        {
            case PI_BAD_GPIO:
            {
                std::cout << gpioPin << "is a bad gpio pin" << std::endl;
                break;
            }

            case PI_BAD_MODE:
            {
                std::cout << "Bad mode specified for gpio pin " << gpioPin << std::endl;
                break;
            }

            default:
            {
                std::cout << "Unexpected error encountered when setting mode specified for gpio pin " << gpioPin << std::endl;
                std::cout << "Result = " << gpioResult << std::endl;
                break;
            }
        }
    }

    return gpioResult;
}