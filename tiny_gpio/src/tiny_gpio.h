#ifndef TINY_GPIO_H
#define TINY_GPIO_H

#include <stdint.h>

#define GPSET0 7
#define GPSET1 8

#define GPCLR0 10
#define GPCLR1 11

#define GPLEV0 13
#define GPLEV1 14

#define GPPUD     37
#define GPPUDCLK0 38
#define GPPUDCLK1 39

#define PI_BANK (gpio>>5)
#define PI_BIT  (1<<(gpio&0x1F))

/* gpio modes. */

#define PI_INPUT  0
#define PI_OUTPUT 1
#define PI_ALT0   4
#define PI_ALT1   5
#define PI_ALT2   6
#define PI_ALT3   7
#define PI_ALT4   3
#define PI_ALT5   2

/* Values for pull-ups/downs off, pull-down and pull-up. */

#define PI_PUD_OFF  0
#define PI_PUD_DOWN 1
#define PI_PUD_UP   2

#ifdef __cplusplus
extern "C" {
#endif

void gpioSetMode(unsigned gpio, unsigned mode);
int gpioGetMode(unsigned gpio);

void gpioSetPullUpDown(unsigned gpio, unsigned pud);
int gpioRead(unsigned gpio);
void gpioWrite(unsigned gpio, unsigned level);
void gpioTrigger(unsigned gpio, unsigned pulseLen, unsigned level);

/* Bit (1<<x) will be set if gpio x is high. */

uint32_t gpioReadBank1(void);
uint32_t gpioReadBank2(void);

/* To clear gpio x bit or in (1<<x). */

void gpioClearBank1(uint32_t bits);
void gpioClearBank2(uint32_t bits);

/* To set gpio x bit or in (1<<x). */

void gpioSetBank1(uint32_t bits);
void gpioSetBank2(uint32_t bits);

unsigned gpioHardwareRevision(void);

int gpioInitialise(void);

#ifdef __cplusplus
}
#endif

#endif // TINY_GPIO_H