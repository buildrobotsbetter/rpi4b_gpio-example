#include <bcm2835.h>
#include <iostream>
#include <fmt/core.h> // For improved string formatting
#include <chrono>
#include <thread>


int main()
{
    // LED is connected to GPIO16 (physical pin 36)
    static unsigned int LED_GPIO_PIN = 16; 

    // Print the pigpio library version
    std::cout << "Using bcm2835 version " << BCM2835_VERSION << std::endl;

    int gpioResult = 0;

    // Initialize the bcm2835 library
    std::cout << "Initializing bcm2835... ";
    gpioResult = bcm2835_init();
    if (gpioResult != 1)
    {
        std::cout << "ERROR" << std::endl;
        return -1;    
    }
    std::cout << "SUCCESS" << std::endl;

    std::cout << "Configuring LED on " << LED_GPIO_PIN << std::endl;

    // Configure the GPIO pin attached to the LED as a output pin
    // PI_OUTPUT is defined within the pigpio library
    bcm2835_gpio_fsel(LED_GPIO_PIN, BCM2835_GPIO_FSEL_OUTP);

    while (true)
    {
        bcm2835_gpio_write(LED_GPIO_PIN, HIGH);
        std::this_thread::sleep_for(std::chrono::seconds(1));

        bcm2835_gpio_write(LED_GPIO_PIN, LOW);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    // Close the bcm2835 library to clean up
    std::cout << "Closing bcm2835... ";
    gpioResult = bcm2835_close();
    if (gpioResult != 1)
    {
        std::cout << "ERROR" << std::endl;
        return -1;    
    }
    std::cout << "SUCCESS" << std::endl;

    return 0;    
}