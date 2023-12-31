- Install pigpio. This is library we will use to control the gpio bins
    - Using apt: `sudo apt-get install pigpio`
    - Check version: `pigpiod -v`
        - We used version 79
- Install CMake. This is the tool we will use to configure our C++ projects
    - Using apt: `sudo apt install cmake`
    - Check version: `cmake --version`
        - We used version 3.18.4


## Additional Info

- Install VS Code C++ Extension to get autocomplete and navigation
- The revision number returned by `gpioHardwareRevision()` matches the revision in `/proc/cpuinfo` 

- pigpio **requires** root access to run
    - https://forums.raspberrypi.com/viewtopic.php?t=180784



## Links

### pigpio
Website: https://abyz.me.uk/rpi/pigpio/index.html
GitHub: https://github.com/joan2937/pigpio

### CMake
Website: https://cmake.org/