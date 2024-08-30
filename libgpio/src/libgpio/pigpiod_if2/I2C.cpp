#include <libgpio/pigpiod_if2/I2C.hpp>

#include <stdexcept>
#include <fmt/core.h>

namespace _libgpio
{
namespace pigpiod_if2
{

I2C::I2C() :
    m_i2cHandle(-1),
    m_busId(0),
    m_deviceAddress(0)
{}

I2C::~I2C()
{
    close();
}

bool I2C::isOpen() const
{
    return m_i2cHandle > 0;
}

uint8_t I2C::getBusId() const
{
    if (!isOpen())
    {
        throw new std::logic_error("I2C channel is not open");
    }

    return m_busId;
}

uint8_t I2C::getDeviceAddress() const
{
    if (!isOpen())
    {
        throw new std::logic_error("I2C channel is not open");
    }

    return m_deviceAddress;
}

void I2C::open(uint8_t busId, uint8_t deviceAddress)
{
    const unsigned int I2C_FLAGS = 0; // There are no flags

    auto result = i2c_open(getGpioHandle(), busId, deviceAddress, I2C_FLAGS);
    if (result == 0)
    {
        m_i2cHandle = result;
        m_busId = busId;
        m_deviceAddress = deviceAddress;
        return;
    }

    switch (result)
    {       
        case PI_BAD_I2C_BUS:
        {
            throw std::invalid_argument(fmt::format("{} is a bad i2c bus id", busId));
        }

        case PI_BAD_I2C_ADDR:
        {
            throw std::invalid_argument(fmt::format("{:x} is a bad i2c address", deviceAddress));
        }

        case PI_BAD_FLAGS:
        {
            throw std::runtime_error(fmt::format("Internal error: {} is an invalid value for the flags", I2C_FLAGS));
        }

        case PI_NO_HANDLE:
        {
            throw std::runtime_error(fmt::format("Internal error: no more I2C objects can be instantiated", I2C_FLAGS));
        }

        case PI_I2C_OPEN_FAILED:
        {
            throw std::runtime_error(fmt::format("I2C communication channel failed to open for unknown reason"));
        }

        default:
        {
            throw std::runtime_error(fmt::format("Unexpected error encountered when opening I2C communication channel on I2C bus {} to device at address {:x} (Error = {})", busId, deviceAddress, result));
        }
    }
}

void I2C::close()
{
    if (isOpen())
    {
        i2c_close(getGpioHandle(), m_i2cHandle);
    }
}

void I2C::write(uint8_t registerAddress, uint8_t value)
{
    auto result = i2c_write_byte_data(getGpioHandle(), m_i2cHandle, registerAddress, value);
    if (result == 0)
    {
        return;
    }

    switch (result)
    {       
        case PI_BAD_HANDLE:
        {
            throw std::runtime_error(fmt::format("Internal error: unknown handle"));
        }

        case PI_BAD_PARAM:
        {
            throw std::invalid_argument(fmt::format("Register address {:x} is invalid", registerAddress));
        }

        case PI_I2C_WRITE_FAILED:
        {
            throw std::runtime_error(fmt::format("I2C write failed"));
        }

        default:
        {
            throw std::runtime_error(fmt::format("Unexpected error encountered when writing data to I2C register {:x} on device at address {:x} using I2C bus {} (Error = {})", registerAddress, m_deviceAddress, m_busId, result));
        }
    }
}

void I2C::read(uint8_t registerAddress, uint8_t& value)
{
    auto result = i2c_read_byte_data(getGpioHandle(), m_i2cHandle, registerAddress);
    if (result >= 0)
    {
        value = static_cast<int8_t>(result);
        return;
    }

    switch (result)
    {       
        case PI_BAD_HANDLE:
        {
            throw std::runtime_error(fmt::format("Internal error: unknown handle"));
        }

        case PI_BAD_PARAM:
        {
            throw std::invalid_argument(fmt::format("Register address {:x} is invalid", registerAddress));
        }

        case PI_I2C_READ_FAILED:
        {
            throw std::runtime_error(fmt::format("I2C read failed"));
        }

        default:
        {
            throw std::runtime_error(fmt::format("Unexpected error encountered when reading data from I2C register {:x} on device at address {:x} using I2C bus {} (Error = {})", registerAddress, m_deviceAddress, m_busId, result));
        }
    }
}

void I2C::read(uint8_t registerAddress, uint16_t& value)
{
    auto result = i2c_read_word_data(getGpioHandle(), m_i2cHandle, registerAddress);
    if (result >= 0)
    {
        value = static_cast<uint16_t>(result);
        return;
    }

    switch (result)
    {       
        case PI_BAD_HANDLE:
        {
            throw std::runtime_error(fmt::format("Internal error: unknown handle"));
        }

        case PI_BAD_PARAM:
        {
            throw std::invalid_argument(fmt::format("Register address {:x} is invalid", registerAddress));
        }

        case PI_I2C_READ_FAILED:
        {
            throw std::runtime_error(fmt::format("I2C read failed"));
        }

        default:
        {
            throw std::runtime_error(fmt::format("Unexpected error encountered when reading data from I2C register {:x} on device at address {:x} using I2C bus {} (Error = {})", registerAddress, m_deviceAddress, m_busId, result));
        }
    }
}

void I2C::read(uint8_t registerAddress, std::vector<uint8_t>& data)
{
    auto result = i2c_read_i2c_block_data(getGpioHandle(), m_i2cHandle, registerAddress, (char*)data.data(), data.size());
    if (result >= 0)
    {
        return;
    }

    switch (result)
    {       
        case PI_BAD_HANDLE:
        {
            throw std::runtime_error(fmt::format("Internal error: unknown handle"));
        }

        case PI_BAD_PARAM:
        {
            throw std::invalid_argument(fmt::format("Register address {:x} is invalid", registerAddress));
        }

        case PI_I2C_READ_FAILED:
        {
            throw std::runtime_error(fmt::format("I2C read failed"));
        }

        default:
        {
            throw std::runtime_error(fmt::format("Unexpected error encountered when reading data from I2C register {:x} on device at address {:x} using I2C bus {} (Error = {})", registerAddress, m_deviceAddress, m_busId, result));
        }
    }
}

} // namespace pigpiod_if2
} // namespace _libgpio
