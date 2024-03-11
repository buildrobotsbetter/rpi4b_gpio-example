

#include <libgpio/MotorDriver.hpp>

#include <iostream>
#include <fmt/core.h> // For improved string formatting
#include <chrono>
#include <thread>

#include <signal.h>


/**
 * Control both the left and right motors of the Viam Rover using the libgpio library
 **/


void printStatus(const libgpio::MotorDriver& left, const libgpio::MotorDriver& right);


bool isRunning = false;
void signalHandler(int signal)
{
    std::cout << "Received signal. Shutting down." << std::endl;
    isRunning = false;
}


int main()
{
    // Left motor is controlled using to GPIO17 (pin 11), GPIO27 (pin 13), and GPIO22 (pin 15)
    static unsigned int IN1_PIN = 17;
    static unsigned int IN2_PIN = 27;
    static unsigned int ENA_PIN = 22;

    // Right motor is controlled using to GPIO23 (pin 16), GPIO24 (pin 18), and GPIO25 (pin 22)
    static unsigned int IN3_PIN = 23; 
    static unsigned int IN4_PIN = 24;
    static unsigned int ENB_PIN = 25;

    // Print the pigpio library version
    std::cout << "Using pigpio version " << gpioVersion() << std::endl;
    std::cout << "Running on " << fmt::format("{:x}", gpioHardwareRevision()) << std::endl;

    signal(SIGINT, signalHandler);

    std::cout << fmt::format("Configuring Left Motor on GPIO {}, {}, & {}... ", IN1_PIN, IN2_PIN, ENA_PIN);
    libgpio::MotorDriver leftMotor(IN1_PIN, IN2_PIN, ENA_PIN);
    std::cout << "SUCCESS" << std::endl;

    std::cout << fmt::format("Configuring Left Motor on GPIO {}, {}, & {}... ", IN3_PIN, IN4_PIN, ENB_PIN);
    libgpio::MotorDriver rightMotor(IN3_PIN, IN4_PIN, ENB_PIN);
    std::cout << "SUCCESS" << std::endl;

    isRunning = true;
    while (isRunning)
    {
        leftMotor.setDirection(libgpio::MotorDirection::FORWARD);
        leftMotor.setEffort_percent(50.0);

        rightMotor.setDirection(libgpio::MotorDirection::FORWARD);
        rightMotor.setEffort_percent(50.0);

        printStatus(leftMotor, rightMotor);

        std::this_thread::sleep_for(std::chrono::seconds(2));

        leftMotor.setEffort_percent(0.0);
        rightMotor.setEffort_percent(0.0);

        printStatus(leftMotor, rightMotor);

        std::this_thread::sleep_for(std::chrono::seconds(2));

        leftMotor.setDirection(libgpio::MotorDirection::BACKWARD);
        leftMotor.setEffort_percent(50.0);

        rightMotor.setDirection(libgpio::MotorDirection::BACKWARD);
        rightMotor.setEffort_percent(50.0);

        printStatus(leftMotor, rightMotor);

        std::this_thread::sleep_for(std::chrono::seconds(2));

        leftMotor.setEffort_percent(0.0);
        rightMotor.setEffort_percent(0.0);

        printStatus(leftMotor, rightMotor);

        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    std::cout << "Cleaning up resources" << std::endl << std::flush;

    return 0;    
}

void printStatus(const libgpio::MotorDriver& leftMotor, const libgpio::MotorDriver& rightMotor)
{
    std::cout << fmt::format("Motors set to left: {} @ {:.2f} % and right: {} @ {:.2f} %", leftMotor.getDirection().toString(), leftMotor.getEffort_percent(), rightMotor.getDirection().toString(), rightMotor.getEffort_percent()) << std::endl;
}