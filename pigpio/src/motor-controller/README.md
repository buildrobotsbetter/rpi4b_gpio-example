## Hardware Connections

In this example, we are using the Viam Rover 1, which comes with an L298N motor driver.
[Viam Rover 1 Documentation](https://docs.viam.com/appendix/try-viam/rover-resources/rover-tutorial-1/)

The pin connections specified in the installation instructions (and verified by the viam configuration):

### Left Motor

- IN1 -- Pin 11 -- GPIO17
- IN2 -- Pin 13 -- GPIO27
- ENA -- Pin 15 -- GPIO22

### Right Motor

- IN3 -- Pin 16 -- GPIO23
- IN4 -- Pin 18 -- GPIO24
- ENB -- Pin 22 -- GPIO25 

According to the viam configuration page, a PWM signal is used on the the ENx pins to control the speed. Given these are not PWM pins on the Raspberry Pi, the PWM signal here is software generated.

## Useful Links

- https://www.raspberrypi.com/documentation/computers/raspberry-pi.html
- https://howtomechatronics.com/tutorials/arduino/arduino-dc-motor-control-tutorial-l298n-pwm-h-bridge/
- https://www.sparkfun.com/datasheets/Robotics/L298_H_Bridge.pdf
