#include <iostream>
#include <lgpio.h>
#include <fmt/core.h>
#include <chrono>
#include <thread>

int main()
{
    // LED is connected to GPIO26 (physical pin 37)
    static unsigned int LED_GPIO_PIN = 26;

    int lgpioResult = 0;

    // Print the lgpio library version
    std::cout << "Using lgpio version " << fmt::format("{:x}", lguVersion()) << std::endl;

    // Get a handle to to the 
    int gpiochip0 = lgGpiochipOpen(0);
    if (gpiochip0 < 0)
    {
        std::cout << "Error opening gpiochip0" << std::endl;
        return -1;
    }

    std::cout << "gpiochip0 opened" << std::endl;

    lgpioResult = lgGpioGetMode(gpiochip0, LED_GPIO_PIN);
    if (lgpioResult < 0)
    {
        std::cout << "Error with lgGpioGetMode" << lgpioResult << std::endl;
        return -1;
    }

    std::cout << "GPIO 26 Mode = " << lgpioResult << std::endl;

    lgpioResult = lgGpioClaimOutput(gpiochip0, 0, LED_GPIO_PIN, 0);
    if (lgpioResult < 0)
    {
        std::cout << "Error claimingGPIO 26 as an output pin" << lgpioResult << std::endl;
        return -1;
    }

    while (true)
    {
        lgpioResult = lgGpioWrite(gpiochip0, LED_GPIO_PIN, 1);
        if (lgpioResult < 0)
        {
            std::cout << "Error setting output on GPIO 26" << lgpioResult << std::endl;
            return -1;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));

        lgpioResult = lgGpioWrite(gpiochip0, LED_GPIO_PIN, 0);
        if (lgpioResult < 0)
        {
            std::cout << "Error setting output on GPIO 26" << lgpioResult << std::endl;
            return -1;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    // Close/clean up the handle
    lgpioResult = lgGpiochipClose(gpiochip0);
    if (lgpioResult < 0)
    {
        std::cout << "Error closing gpiochip0" << std::endl;
        return -1;
    }

    return 0;
}
