#include <pigpio.h>
#include <iostream>
#include <fmt/core.h> // For improved string formatting
#include <chrono>
#include <thread>


bool configurePull(unsigned gpio, unsigned pull);
bool configurePin(unsigned gpio, unsigned mode);


int main()
{
    // DIP Switch is connected to GPIO27 (physical pin 13)
    static unsigned int SWITCH_GPIO_PIN = 27; 

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

    std::cout << "Configuring Switch on " << SWITCH_GPIO_PIN << std::endl;

    // Configure the pull-up resistor on GPIO pin attached to the Switch
    // GPIO 27 boots with pull down resistor, but we explicit configure it in case it was changed by another piece of software
    // PI_PUD_DOWN is defined within the pigpio library
    if (!configurePull(SWITCH_GPIO_PIN, PI_PUD_DOWN))
    {
        return -1;
    }

    // Configure the GPIO pin attached to the LED as a input pin
    // PI_OUTPUT is defined within the pigpio library
    if (!configurePin(SWITCH_GPIO_PIN, PI_INPUT))
    {
        return -1;
    }

    bool switchState = false;
    while (true)
    {
        int gpioResult = gpioRead(SWITCH_GPIO_PIN);
        if (gpioResult < 0)
        {
            std::cout << "Unexpected error encountered when reading from  gpio pin " << SWITCH_GPIO_PIN << std::endl;
            std::cout << "Result = " << gpioResult << std::endl;
        }

        // Positive logic, HIGH = True, LOW = False
        bool isActive = (gpioResult == 1);

        bool newSwitchState = isActive;

        if (switchState != newSwitchState)
        {
            switchState = newSwitchState;
            std::cout << "State = " << (newSwitchState ? "Active" : "NOT Active") << std::endl;   
        }
    }

    // Terminate the pigpio library to clean up
    gpioTerminate();

    return 0;    
}


bool configurePull(unsigned gpio, unsigned pud)
{
    int gpioResult = gpioSetPullUpDown(gpio, pud);

    // Check the result to ensure the GPIO pin could be properly configured
    if (gpioResult != 0) // A value of 0 = OK
    {
        switch (gpioResult)
        {
            case PI_BAD_GPIO:
            {
                std::cout << gpio << "is a bad gpio pin" << std::endl;
                return false;
            }

            case PI_BAD_PUD:
            {
                std::cout << "Bad pull specified for gpio pin " << gpio << std::endl;
                return false; 
            }

            default:
            {
                std::cout << "Unexpected error encountered when setting pull specified for gpio pin " << gpio << std::endl;
                std::cout << "Result = " << gpioResult << std::endl;
                return false;
            }
        }
    }

    return true;
}


/// @brief Configure the gpio pin with the specified mode
/// @param gpio 
/// @param mode 
/// @return True if successful, False otherwise 
bool configurePin(unsigned gpio, unsigned mode)
{
    int gpioResult = gpioSetMode(gpio, mode);

    // Check the result to ensure the GPIO pin could be properly configured
    if (gpioResult != 0) // A value of 0 = OK
    {
        switch (gpioResult)
        {
            case PI_BAD_GPIO:
            {
                std::cout << gpio << "is a bad gpio pin" << std::endl;
                return false;
            }

            case PI_BAD_MODE:
            {
                std::cout << "Bad mode specified for gpio pin " << gpio << std::endl;
                return false; 
            }

            default:
            {
                std::cout << "Unexpected error encountered when setting mode specified for gpio pin " << gpio << std::endl;
                std::cout << "Result = " << gpioResult << std::endl;
                return false;
            }
        }
    }

    return true;
}