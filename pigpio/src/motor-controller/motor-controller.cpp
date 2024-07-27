#include <pigpio.h>

#include <iostream>
#include <fmt/core.h> // For improved string formatting
#include <chrono>
#include <thread>

#include <signal.h>


/**
 * Control the left motor of the Viam Rover using the pigpio functions directly
 **/


bool configurePins(unsigned in1, unsigned in2, unsigned enable);
bool configurePinAsOutput(unsigned gpio);

bool isRunning = false;
void signalHandler(int signal)
{
    std::cout << "Received signal. Shutting down." << std::endl;
    isRunning = false;
}


int main()
{
    // Left motor is controlled using to GPIO17, GPIO27, and GPIO22
    static unsigned int IN1_PIN = 17;
    static unsigned int IN2_PIN = 27;
    static unsigned int ENA_PIN = 22;

    // // Right motor is controlled using to GPIO23 (pin 16), GPIO24 (pin 18), and GPIO25 (pin 22)
    // static unsigned int IN1_PIN = 23; 
    // static unsigned int IN2_PIN = 24;
    // static unsigned int ENA_PIN = 25;

    int gpioResult = 0;

    // Print the pigpio library version
    std::cout << "Using pigpio version " << gpioVersion() << std::endl;
    std::cout << "Running on " << fmt::format("{:x}", gpioHardwareRevision()) << std::endl;

    // Disable built-in pigpio signal handling
    // Must be called before gpioInitialise()
    int cfg = gpioCfgGetInternals();
    cfg |= PI_CFG_NOSIGHANDLER;
    gpioCfgSetInternals(cfg);

    signal(SIGINT, signalHandler);

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

    std::cout << fmt::format("Configuring GPIO {}, {}, & {}... ", IN1_PIN, IN2_PIN, ENA_PIN);
    if (!configurePins(IN1_PIN, IN2_PIN, ENA_PIN))
    {
        return -1;
    }
    std::cout << "SUCCESS" << std::endl;


    gpioResult = gpioWrite(IN1_PIN, 1);
    if (gpioResult != 0)
    {
        std::cout << fmt::format("Error {} occurred while writing to GPIO {}", gpioResult, IN1_PIN) << std::endl << std::flush;
        return -1;
    }

    gpioResult = gpioWrite(IN2_PIN, 0);
    if (gpioResult != 0)
    {
        std::cout << fmt::format("Error {} occurred while writing to GPIO {}", gpioResult, IN2_PIN) << std::endl << std::flush;
        return -1;
    }

    const unsigned int PWM_DUTY_CYCLE = 128; // 128 = 50% (128/255)
    std::cout << fmt::format("Setting PWM to {}", PWM_DUTY_CYCLE) << std::endl << std::flush;        
    gpioResult = gpioPWM(ENA_PIN, PWM_DUTY_CYCLE);
    if (gpioResult != 0)
    {
        std::cout << fmt::format("Error {} occurred while setting to PWM on GPIO {}", gpioResult, ENA_PIN) << std::endl << std::flush;
        return -1;
    }

    isRunning = true;
    while (isRunning)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    gpioResult = gpioPWM(ENA_PIN, 0);  // Stop
    if (gpioResult != 0)
    {
        std::cout << fmt::format("Error {} occurred while setting to PWM on GPIO {}", gpioResult, ENA_PIN) << std::endl << std::flush;
    }

    // Terminate the pigpio library to clean up
    std::cout << "Cleaning up pigpio" << std::endl << std::flush;
    gpioTerminate();

    return 0;    
}

/// @brief Configure the gpio pins as output for motor control
/// @param in1 the IN1 pin
/// @param in2 the IN2 pin
/// @param enable the IN2 pin
/// @return True if successful, False otherwise
bool configurePins(unsigned in1, unsigned in2, unsigned enable)
{
    if (!configurePinAsOutput(in1))
    {
        return false;
    }

    if (!configurePinAsOutput(in2))
    {
        return false;
    }

    if (!configurePinAsOutput(enable))
    {
        return false;
    }

    return true;
}

/// @brief Configure the gpio pin as an output pin
/// @param gpio 
/// @return True if successful, False otherwise 
bool configurePinAsOutput(unsigned gpio)
{
    int gpioResult = gpioSetMode(gpio, PI_OUTPUT);

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