#ifndef print_h
#define print_h

#include <stdio.h>
#include "print.h"
#include <stdint.h>

#define GPIO_OPEN1 ("/sys/class/gpio/export")

#define GPIO_VALUE1(n) ("/sys/class/gpio/gpio" #n "/value")
#define GPIO_VALUE2(n) GPIO_VALUE1(n)

#define GPIO_DIRECTION1(n) ("/sys/class/gpio/gpio" #n "/direction")
#define GPIO_DIRECTION2(n) GPIO_DIRECTION1(n)

#define LED_NUM 4
#define LED_OFF "0"
#define LED_ON "1"

void toggle ( uint8_t led);
void *  thread (void *);
void initiate_out (void);


#endif /* print_h */
