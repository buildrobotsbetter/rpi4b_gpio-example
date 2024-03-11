# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).


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
