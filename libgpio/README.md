# README

A C++ wrapper library around the `pigpio` and `pigpiod` functionality to control the GPIO pins on the Raspberry Pi 4B. The classes in this library are intended to simplify the interface required to control the hardware and abstract the low-level details of the hardware control library.

## Dependencies

Depends on:
- The [pigpio](http://abyz.me.uk/rpi/pigpio/) library for GPIO control
- The [{fmt}](https://github.com/fmtlib/fmt) library for string formatting


## Dependency Installation

### pigpio

#### Linux:

Taken from the [pigpio website](http://abyz.me.uk/rpi/pigpio/download.html).

```bash
wget https://github.com/joan2937/pigpio/archive/master.zip
unzip master.zip
cd pigpio-master
make
sudo make install
```

### {fmt}

#### Linux:

```bash
sudo add-apt-repository universe
sudo apt update
sudo apt install libfmt-dev
```
