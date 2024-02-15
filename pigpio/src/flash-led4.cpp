#include <libgpio/LED.hpp>

#include <pigpio.h>

#include <iostream>
#include <fmt/core.h> // For improved string formatting
#include <chrono>
#include <thread>
#include <signal.h>


bool isRunning = false;
void signalHandler(int signal)
{
    isRunning = false;
}

int main()
{
    static unsigned int LED_GPIO_PIN1 = 26; 
    static unsigned int LED_GPIO_PIN2 = 16; 

    signal(SIGINT, signalHandler);

    // Print the pigpio library version
    std::cout << "Using pigpio version " << gpioVersion() << std::endl;
    std::cout << "Running on " << fmt::format("{:x}", gpioHardwareRevision()) << std::endl;

    std::cout << "Configuring LED on " << LED_GPIO_PIN1 << std::endl;
    auto led1 = libgpio::LED(LED_GPIO_PIN1);

    std::cout << "Configuring LED on " << LED_GPIO_PIN2 << std::endl;
    auto led2 = libgpio::LED(LED_GPIO_PIN2);

    isRunning = true;
    while (isRunning)
    {
        led1.setOutput(true);
        led2.setOutput(false);
        std::this_thread::sleep_for(std::chrono::milliseconds(300));

        led1.setOutput(false);
        led2.setOutput(true);
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }

    led1.setOutput(false);
    led2.setOutput(false);

    return 0;    
}
