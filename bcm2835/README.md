- Install bcm2835. This is library we will use to control the gpio bins
    - https://www.airspayce.com/mikem/bcm2835/index.html
        - `wget`
        - `tar -xvf`
        - `configure`
        - `make`
        - `sudo make install`
        - We used version 1.73
- Install CMake. This is the tool we will use to configure our C++ projects
    - Using apt: `sudo apt install cmake`
    - Check version: `cmake --version`
        - We used version 3.18.4


## Additional Info

- Install VS Code C++ Extension to get autocomplete and navigation
- The revision number returned by `gpioHardwareRevision()` matches the revision in `/proc/cpuinfo` 

For full bcm2835 functionality, you need to run as root. See documentation linked at top.



## Links

### CMake
Website: https://cmake.org/