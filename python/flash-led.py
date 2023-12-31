from gpiozero import LED
from time import sleep

led_gpio_pin = 26  # LED is connected to GPIO26 (physical pin 37)

print(f"Configuring LED on {led_gpio_pin}")

led = LED(led_gpio_pin)

print(f"Flashing LED")

while True:
    led.on()
    sleep(1)
    led.off()
    sleep(1)
