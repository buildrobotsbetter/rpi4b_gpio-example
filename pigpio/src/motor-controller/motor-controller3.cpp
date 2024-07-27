#include <libgpio/MotorDriver.hpp>
#include <libgpio/Utilities.hpp>

#include <iostream>
#include <fmt/core.h> // For improved string formatting
#include <chrono>
#include <thread>

#include <signal.h>


/**
 * Switch the direction the left motor of the Viam Rover
 **/


bool isRunning = false;
void signalHandler(int signal)
{
    std::cout << "Received signal. Shutting down." << std::endl;
    isRunning = false;
}


int main()
{
    // Left motor is controlled using to GPIO17, GPIO27, and GPIO22
    static unsigned int IN1_PIN = 27;
    static unsigned int IN2_PIN = 17;
    static unsigned int ENA_PIN = 22;

    // Print the pigpio library version
    // std::cout << "Using pigpio version " << gpioVersion() << std::endl;
    // std::cout << "Running on " << fmt::format("{:x}", gpioHardwareRevision()) << std::endl;
    std::cout << "Using libgpio version: " << libgpio::version() << std::endl;
    std::cout << "Using gpio library: " << libgpio::gpioLibrary() << std::endl;

    signal(SIGINT, signalHandler);

    std::cout << fmt::format("Configuring Left Motor on GPIO {}, {}, & {}... ", IN1_PIN, IN2_PIN, ENA_PIN);
    libgpio::MotorDriver leftMotor(IN1_PIN, IN2_PIN, ENA_PIN);
    std::cout << "SUCCESS" << std::endl;

    isRunning = true;
    while (isRunning)
    {
        leftMotor.setDirection(libgpio::MotorDirection::FORWARD);
        leftMotor.setEffort_percent(50.0);

        std::cout << fmt::format("Left motor set to {} % effort in {} direction", leftMotor.getEffort_percent(), leftMotor.getDirection().toString()) << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(2));

        leftMotor.setEffort_percent(0.0);

        std::cout << fmt::format("Left motor set to {} % effort in {} direction", leftMotor.getEffort_percent(), leftMotor.getDirection().toString()) << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(2));

        leftMotor.setDirection(libgpio::MotorDirection::BACKWARD);
        leftMotor.setEffort_percent(50.0);

        std::cout << fmt::format("Left motor set to {} % effort in {} direction", leftMotor.getEffort_percent(), leftMotor.getDirection().toString()) << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(2));

        leftMotor.setEffort_percent(0.0);

        std::cout << fmt::format("Left motor set to {} % effort in {} direction", leftMotor.getEffort_percent(), leftMotor.getDirection().toString()) << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    std::cout << "Cleaning up resources" << std::endl << std::flush;

    return 0;    
}
