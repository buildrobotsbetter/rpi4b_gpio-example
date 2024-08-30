# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).


## [1.4.0] - In-Development

### Fixed
- Updates links to Viam Rover 1 documentation within subtopic README.md files (when applicable)


## [1.3.1] - 2024-07-26

### Changed
- Migrate to using `libgpio v0.1.0` cloned from separate repository using [git-subrepo](https://github.com/ingydotnet/git-subrepo).
    - No change in usage


## [1.3.0] - 2024-07-13

### Added
- Examples showing how to use I2C to communicate with an accelerometer (ADXL345) when using the `pigpio` library functions
- `I2C` class to `libgpio` library which encapsulates the `pigpio` I2C functionality

### Changed
- Change `DigitalOutput` class in `libgpio` library to throw a `std::invalid_argument` exception when provided with a bad gpio pin value instead of a `std::runtime_error` exception.


## [1.2.0] - 2024-03-10

### Added
- Examples showing how to control a motor when using the `pigpio` library functions
- `MotorDriver` class to `libgpio` library which encapsulates the `pigpio` motor control functionality
- `DigitalOutput` class to `libgpio` library which represents a generic digital output pin

### Changed
- Refactor `LED` class in `libgpio` library to use newly added`DigitalOutput` class


## [1.1.0] - 2024-02-15

### Added
- Examples showing how to set a custom signal handler when using the `pigpio` library
- Examples showing how to read a swich using the `pigpio` library
- `libgpio` library that encapsulates the LED and Switch functionality using the `pigpio` library into C++ classes
- Examples showing how to use the `libgpio` library to control an LED and read a switch
- `CHANGELOG.md` file to keep track of changes in the project


## [1.0.0] - 2023-12-31

### Added
- Examples showing how to control an LED using multiple libaries (`pigpio`, `lgpio`, `bcm2835`, etc)
