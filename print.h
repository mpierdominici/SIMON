/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   print.h
 * Author: matias
 *
 * Created on 29 de noviembre de 2016, 13:29
 */

#ifndef PRINT_H
#define PRINT_H
#include <stdint.h>
#ifndef RPI_MODE
int8_t iniciar_alegro(void);
int8_t iniciar_variables_print_allegro(void);
void print_stage_simon(void);
void destroy_print (void);
void setear_botones_imprimir(void);
void * print_botones(void *);
void set_print_stage_simon(uint8_t * arreglo_de_secuencias,uint8_t stage_simon);
void stop_all_thread(void);
#endif//allegro mode



#ifdef __cplusplus
extern "C" {
#endif




#ifdef __cplusplus
}
#endif

#endif /* PRINT_H */
