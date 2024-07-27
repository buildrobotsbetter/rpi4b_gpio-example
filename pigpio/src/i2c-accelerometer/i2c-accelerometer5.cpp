#include <libgpio/I2C.hpp>
#include <libgpio/Utilities.hpp>

#include <iostream>
#include <fmt/core.h> // For improved string formatting
#include <chrono>
#include <thread>

#include <signal.h>


bool isRunning = false;

void signalHandler(int signal)
{
    std::cout << "Received signal. Shutting down." << std::endl;
    isRunning = false;
}


int main()
{
    try
    {
        static unsigned int I2C_BUS = 1;
        static unsigned int AXDL345_ADDR = 0x53;

        // Print the pigpio library version
        // std::cout << "Using pigpio version " << gpioVersion() << std::endl;
        // std::cout << "Running on " << fmt::format("{:x}", gpioHardwareRevision()) << std::endl;
        std::cout << "Using libgpio version: " << libgpio::version() << std::endl;
        std::cout << "Using gpio library: " << libgpio::gpioLibrary() << std::endl;

        signal(SIGINT, signalHandler);

        // Instantiate an I2C object for the communication with the accelerometer
        libgpio::I2C axdl345; 

        // Open the connection the accelerometer
        std::cout << fmt::format("Configuring I2C Bus {} to communicate with device at address {}... ", I2C_BUS, AXDL345_ADDR);
        axdl345.open(I2C_BUS, AXDL345_ADDR);
        std::cout << "SUCCESS" << std::endl;


        // -- Initialize the ADXL345
        std::cout << fmt::format("Configuring for full resolution, +/- 16g range... ");
        axdl345.write(0x31, 0b00001011); // FULL_RES, Range=+/-16g
        std::cout << "SUCCESS" << std::endl;

        std::cout << fmt::format("Starting measurements... ");
        axdl345.write(0x2D, 0b00001000); // Measure
        std::cout << "SUCCESS" << std::endl;

        isRunning = true;
        while (isRunning)
        {
            std::vector<uint8_t> data(6);
            axdl345.read(0x32, data);

            int16_t dataX_1 = (data[1] << 8) | data[0];
            int16_t dataY_1 = (data[3] << 8) | data[2];
            int16_t dataZ_1 = (data[5] << 8) | data[4];

            // 13-bits = 2^13 possible values = 8192 possible values
            // measurement range = +/- 16g = (16g) - (-16g) = 32g full range
            const double scale = ((16) - (-16)) / (double)(8192);
            const double g_mps2 = 9.8;

            double x_g = dataX_1 * scale;
            double x_mps2 = x_g * g_mps2;

            double y_g = dataY_1 * scale;
            double y_mps2 = y_g * g_mps2;

            double z_g = dataZ_1 * scale;
            double z_mps2 = z_g * g_mps2;

            std::cout << fmt::format("X: {} g = {} m/s^2", x_g, x_mps2) << std::endl;
            std::cout << fmt::format("Y: {} g = {} m/s^2", y_g, y_mps2) << std::endl;
            std::cout << fmt::format("Z: {} g = {} m/s^2", z_g, z_mps2) << std::endl;
            std::cout << std::endl;

            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        axdl345.close();
    }
    catch (const std::exception& ex)
    {
        std::cout << "Exception occurred! " << std::endl;
        std::cout << ex.what() << std::endl;
        std::cout << std::endl;
        std::cout << "Terminating application. " << ex.what() << std::endl;
    }

    return 0;    
}
