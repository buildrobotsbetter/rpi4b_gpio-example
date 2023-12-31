- Build and install lg source. This is library we will use to control the gpio bins

- Install CMake. This is the tool we will use to configure our C++ projects
    - Using apt: `sudo apt install cmake`
    - Check version: `cmake --version`
        - We used version 3.18.4


## Additional Info

- Install VS Code C++ Extension to get autocomplete and navigation
- The revision number returned by `gpioHardwareRevision()` matches the revision in `/proc/cpuinfo` 

- You need to configure the root access to use hardware?
    - See:
        - https://www.raspberrypi.com/documentation/computers/raspberry-pi.html#permissions
        - https://roboticsbackend.com/raspberry-pi-hardware-permissions/
    - Checked what was said in above and everything seemed okay. Looking at the pigpio code (pigpio.c:7360), it checks for correct permissions by trying to open the `/dev/mem` file. The permissions on that file are `crw-r----- 1 root kmem 1, 1 Dec  1 15:57 /dev/mem`. The need to run using sudo seems like a bug in pigpio.



## Links

### lg
Website: http://abyz.me.uk/lg/index.html
GitHub: https://github.com/joan2937/lg

### CMake
Website: https://cmake.org/