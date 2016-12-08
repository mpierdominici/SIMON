/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   input.h
 * Author: matias
 *
 * Created on 30 de noviembre de 2016, 11:53
 */

#ifndef INPUT_H
#define INPUT_H
#include  "modo_compilacion.h"
#include <stdint.h>
#ifndef RPI_MODE

void set_input (void * display);
#endif//******ALEGRO**********

int8_t inicializar_input(void);
int8_t get_boton (void);

#ifdef __cplusplus
extern "C" {
#endif




#ifdef __cplusplus
}
#endif

#endif /* INPUT_H */

