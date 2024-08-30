#ifndef LIBGPIO_PIGPIO_I2C
#define LIBGPIO_PIGPIO_I2C

#include <libgpio/pigpio/Device.hpp>

#include <vector>

namespace _libgpio
{
namespace pigpio
{
    
class I2C : public Device
{
public:
    I2C();
    ~I2C() override;

    /// @brief Check if the I2C communication channel is open
    /// @return 
    bool isOpen() const;

    /// @brief Get the I2C Bus ID associated with the open I2C channel
    /// @return 
    uint8_t getBusId() const;

    /// @brief Get the I2C address of the device associated with the open I2C channel
    /// @return 
    uint8_t getDeviceAddress() const;

    /// @brief Open an I2C communication channel to an I2C device
    /// @param busId the I2C bus to be used for communication
    /// @param deviceAddress the address of the device to be communicated with
    void open(uint8_t busId, uint8_t deviceAddress);
    
    /// @brief Close the I2C communcation channel
    void close();

    void write(uint8_t registerAddress, uint8_t value);

    /// @brief Read a uint8 value from the provided register address
    /// @param registerAddress
    /// @param value
    /// @return 
    void read(uint8_t registerAddress, uint8_t& data);

    /// @brief Read a uint16 value from the provided register address
    /// I2C only supports single byte transfers. As such, reading a uint16
    /// value reads the lower byte (LSB) from the register address provided
    /// and the upper byte (MSB) from the register address immediately
    /// following the address provided (little endian).
    /// Example: 
    ///    Given the following register contents:
    ///    --------------|--------------
    ///     Register     | Contents
    ///    --------------|--------------
    ///     ...          |
    ///     0x32         | 0x05
    ///     0x33         | 0x1A
    ///     0x34         | 0xFD
    ///     0x35         | 0x92
    ///     ...          |
    ///    --------------|--------------
    /// 
    ///    Using this method will return the following results:
    ///      + read(0x32, _) --> 0x1A05  (LSB = Register 0x32, MSB = Register 0x33)
    ///      + read(0x33, _) --> 0xFD1A  (LSB = Register 0x33, MSB = Register 0x34)
    ///      + read(0x34, _) --> 0x92FD  (LSB = Register 0x34, MSB = Register 0x35)
    ///
    /// @param registerAddress
    /// @param value
    /// @return 
    void read(uint8_t registerAddress, uint16_t& value);

    /// @brief Read a block of bytes/uint8 values from the provided register address
    /// The number of bytes to be read is the size of the provided std::vector
    /// I2C only supports single byte transfers. As such, reading a block of bytes
    /// reads bytes starting from the the register address and incrementing the
    /// address until the total number of bytes are read 
    /// Example:
    ///    Given the following register contents:
    ///    --------------|--------------
    ///     Register     | Contents
    ///    --------------|--------------
    ///     ...          |
    ///     0x32         | 0x05
    ///     0x33         | 0x1A
    ///     0x34         | 0xFD
    ///     0x35         | 0x92
    ///     ...          |
    ///    --------------|--------------
    /// 
    ///    Using this method will return the following results:
    ///      + read(0x32, 2, _) --> [0x05, 0x1A]
    ///      + read(0x32, 4, _) --> [0x05, 0x1A, 0xFD, 0x92]
    ///      + read(0x33, 3, _) --> [0x1A, 0xFD, 0x92]
    ///
    /// @param registerAddress 
    /// @param data 
    void read(uint8_t registerAddress, std::vector<uint8_t>& data);

private:
    int m_i2cHandle;
    uint8_t m_busId;
    uint8_t m_deviceAddress;
};

} // namespace pigpio
} // namespace _libgpio

#endif // LIBGPIO_PIGPIO_I2C
