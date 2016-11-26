#ifndef T1PIN_H
#define T1PIN_H

#include "pin.h"
#define M_INPUT 0
#define M_OUTPUT 1
#define M_HIGH 1
#define M_LOW 0

void set_gpio(MPIN * gpio_pines);
int export_gpio(char npin);
int unexport_gpio(char npin);
int direction_gpio(char direction ,char npin);
int value_gpio(char value ,char npin);
#endif
