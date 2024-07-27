#include <pigpio.h>

#include <iostream>
#include <fmt/core.h> // For improved string formatting
#include <chrono>
#include <thread>

#include <signal.h>


int configureI2C(unsigned, unsigned, unsigned);
short readWord(int, unsigned char);
bool writeByte(int, unsigned char, unsigned char);


bool isRunning = false;

void signalHandler(int signal)
{
    std::cout << "Received signal. Shutting down." << std::endl;
    isRunning = false;
}


int main()
{
    static unsigned int I2C_BUS = 1;
    static unsigned int AXDL345_ADDR = 0x53;
    static unsigned int I2C_FLAGS = 0; // There are no flags

    int pigpioResult = 0;

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
    pigpioResult = gpioInitialise();
    if (pigpioResult == PI_INIT_FAILED)
    {
        std::cout << "ERROR" << std::endl;
        std::cout << "Error value = " << pigpioResult << std::endl;
        return -1;    
    }
    std::cout << "SUCCESS" << std::endl;

    // Get a handle to the I2C bus
    std::cout << fmt::format("Configuring I2C Bus {} to communicate with device at address {}... ", I2C_BUS, AXDL345_ADDR);
    int i2cHandle = i2cOpen(I2C_BUS, AXDL345_ADDR, I2C_FLAGS);
    if (i2cHandle < 0)
    {
        return -1;
    }
    std::cout << "SUCCESS" << std::endl;


    // -- Initialize the ADXL345
    std::cout << fmt::format("Configuring for full resolution, +/- 16g range... ");
    if (!writeByte(i2cHandle, 0x31, 0b00001011)) // FULL_RES, Range=+/-16g
    // if (!writeByte(i2cHandle, 0x31, 0b10001011)) // SELF_TEST, FULL_RES, Range=+/-16g
    {
        return -1;
    }
    std::cout << "SUCCESS" << std::endl;


    std::cout << fmt::format("Starting measurements... ");
    if (!writeByte(i2cHandle, 0x2D, 0b00001000)) // Measure
    {
        return -1;
    }
    std::cout << "SUCCESS" << std::endl;


    isRunning = true;
    while (isRunning)
    {
        short dataX_1 = readWord(i2cHandle, 0x32);
        short dataY_1 = readWord(i2cHandle, 0x34);
        short dataZ_1 = readWord(i2cHandle, 0x36);

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

    std::cout << "Closing I2C Bus... ";
    pigpioResult = i2cClose(i2cHandle);
    if (pigpioResult < 0)
    {
        std::cout << "ERROR" << std::endl;
        std::cout << fmt::format("Error closing i2c (Error: {})", pigpioResult) << std::endl;
    }
    else
    {
        std::cout << "SUCCESS" << std::endl;
    }

    // Terminate the pigpio library to clean up
    std::cout << "Cleaning up pigpio" << std::endl << std::flush;
    gpioTerminate();

    return 0;    
}


int configureI2C(unsigned i2cBus, unsigned i2cAddr, unsigned i2cFlags)
{
    int i2cHandle = i2cOpen(i2cBus, i2cAddr, i2cFlags);

    // Check the result to ensure the I2C bus could be properly configured
    if (i2cHandle < 0) // A value of 0 = OK
    {
        switch (i2cHandle)
        {
            case PI_BAD_I2C_BUS:
            {
                std::cout << "Bad i2c bus specified" << std::endl;
                break;
            }

            case PI_BAD_I2C_ADDR:
            {
                std::cout << "Bad i2c address specified" << std::endl;
                break;
            }

            case PI_BAD_FLAGS:
            {
                std::cout << "Bad i2c flags specified" << std::endl;
                break;
            }

            case PI_NO_HANDLE:
            {
                std::cout << "No i2c handles available" << std::endl;
                break;
            }

            case PI_I2C_OPEN_FAILED:
            {
                std::cout << "i2c open failed " << std::endl;
                break;
            }

            default:
            {
                std::cout << "Unexpected error encountered when opening i2c" << std::endl;
                std::cout << "Result = " << i2cHandle << std::endl;
                break;
            }
        }
    }

    return i2cHandle;
}


short readWord(int i2cHandle, unsigned char regAddr)
{
    int pigpioResult = i2cReadWordData(i2cHandle, regAddr);
    if (pigpioResult < 0)
    {
        std::cout << fmt::format("Error with i2cReadWordData (Error: {})", pigpioResult) << std::endl;
    }

    return (short)pigpioResult;
}

short read2Bytes(int i2cHandle, unsigned char regAddrLow, unsigned char regAddrHigh)
{
    int data0 = i2cReadByteData(i2cHandle, regAddrLow);
    if (data0 < 0)
    {
        std::cout << fmt::format("Error with i2cReadByteData({:x}) (Error: {})", regAddrLow, data0) << std::endl;            
    }

    int data1 = i2cReadByteData(i2cHandle, regAddrHigh);
    if (data1 < 0)
    {
        std::cout << fmt::format("Error with i2cReadByteData({:x}) (Error: {})", regAddrHigh, data1) << std::endl;            
    }
    
    short data = (data1 << 8) | data0; 
    return data;
}

bool writeByte(int i2cHandle, unsigned char regAddr, unsigned char value)
{
    int pigpioResult = i2cWriteByteData(i2cHandle, regAddr, value);
    if (pigpioResult != 0)
    {
        std::cout << fmt::format("Error with i2cWriteByteData({:x}) (Error: {})", regAddr, pigpioResult) << std::endl;               
        return false;
    }

    return true;
}
