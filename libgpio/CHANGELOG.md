# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).


## [0.2.0] - 2024-08-27

### Added
- Support for `pigpiod_if2`
    - Enable using `-DLIBGPIO_USE_PIGPIOD_IF2=ON` with cmake

### Fixed
- `pigpio` MotorDriver effort percent to PWM duty cycle conversion
    - Conversion was incorrectly using percentage instead of decimal, i.e. 10.0 (percent) * 255 (max PWM) instead of 0.1 (decimal) * 255 (max PWM).


## [0.1.0] - 2024-07-26

### Added
- Migrated files from [rpi4b_gpio-example](https://github.com/buildrobotsbetter/rpi4b_gpio-example) v1.3.0
- Added `CHANGELOG.md` file
