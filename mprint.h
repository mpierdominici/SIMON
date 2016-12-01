
#ifndef PRINT_H
#define PRINT_H

#include <stdio.h>
#include <stdint.h>
#include "pin.h"
#include "boole.h"

#define	M_OUTPUT 0
#define M_INPUT 1
#define M_HIGH 1
#define M_LOW 0

char estado_botones []={0};

void set_gpio(MPIN * gpio_pines);
int export_gpio(char npin);
int unexport_gpio(char npin);
int direction_gpio(char direction ,char npin);
int value_gpio(char value ,char npin);
void * thread (void *);
void changeled_state (char state, char i);
char * read_value (char npin);

//void juego (MPIN pines []);

#endif /* PRINT_H*/
