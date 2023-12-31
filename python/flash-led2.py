from gpiozero import LED
from time import sleep

led_gpio_pin = 16  # LED is connected to GPIO16 (physical pin 36)

print(f"Configuring LED on {led_gpio_pin}")

led = LED(led_gpio_pin)

print(f"Flashing LED")

while True:
    led.on()
    sleep(1)
    led.off()
    sleep(1)
