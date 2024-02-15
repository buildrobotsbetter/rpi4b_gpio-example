from gpiozero import LED, Button
from time import sleep

led_gpio_pin = 26  # LED is connected to GPIO26 (physical pin 37)
switch_gpio_pin = 27  # Switch is connected to GPIO27 (physical pin 13)

print(f"Configuring LED on {led_gpio_pin}")
led = LED(led_gpio_pin)

switch = Button(switch_gpio_pin, pull_up=False)
print(f"Configuring LED on {led_gpio_pin}")

current_state = False

while True:
    # if switch.is_active:
    #     desired_sleep_time_sec = 1.0
    # else:
    #     desired_sleep_time_sec = 0.5

    # if sleep_time_sec != desired_sleep_time_sec:
    #     sleep_time_sec = desired_sleep_time_sec
    #     print(f"Flashing every {sleep_time_sec}")

    # led.on()
    # sleep(sleep_time_sec)

    # led.off()
    # sleep(sleep_time_sec)

    new_state = switch.is_active
    if current_state != new_state:
        current_state = new_state
        print(f"State = {'Active' if new_state else 'NOT Active'}")

    # sleep(2.0)
