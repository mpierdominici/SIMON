/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdio.h>
#include <stdlib.h>
#include "boole.h"
#include "input.h"
#include "print.h"

#ifndef RPI_MODE

#include <allegro5/allegro.h>

static ALLEGRO_DISPLAY *pantalla =NULL;//se alamacena el display de sonde se obtendran las cordenadas de los clicks
static ALLEGRO_EVENT_QUEUE *cola_de_eventos =NULL;//cola de eventos para los clicks
enum{PRIMER_CUADRANTE = 1 ,SEGUNDO_CUADRANTE,TERCER_CUADRANTE,CUARTO_CUADRANTE};//numeros que representan cada cuadrante


uint8_t cuadrante (int16_t x,int16_t y);

//inicializar_input
//recive:nada
//devuelve:M_error si no se pudo inicializar correctamente input
//NOTA:primero se deve ejecutar set_input para que no halla errores
//
static ALLEGRO_EVENT eventos;
int8_t inicializar_input(void)
{
    
      cola_de_eventos = al_create_event_queue();
   if(!cola_de_eventos) {
      fprintf(stderr, "failed to create event_queue!\n");
      return M_ERROR;
   }
    
    if(!al_install_mouse()) 
    {
        fprintf(stderr, "failed to initialize the mouse!\n");
        return M_ERROR;
    }
    if(pantalla==NULL||cola_de_eventos==NULL)
    {
        return M_ERROR;
    }
  
    al_register_event_source(cola_de_eventos, al_get_display_event_source(pantalla));
    al_register_event_source(cola_de_eventos, al_get_mouse_event_source()); 
    return M_FALSE;
}

//set_input
//recive:puntero a void. que se interpretara como puntero a display
void set_input (void * display)
{
   pantalla= (ALLEGRO_DISPLAY *)display;
}

//get_boton
//recive:nada
//devuelve:el boton presionado. un numero entre 1 y 4
//accion: prende el led del boton presionado
//
int8_t get_boton (void)
{
    int8_t devuelve=M_FALSE;
    al_get_next_event(cola_de_eventos, &eventos);
    if(eventos.type==ALLEGRO_EVENT_MOUSE_BUTTON_UP)
    {
        print_a_button(1,M_FALSE);
        print_a_button(2,M_FALSE);
        print_a_button(3,M_FALSE);
        print_a_button(4,M_FALSE);

        devuelve=cuadrante(eventos.mouse.x,eventos.mouse.y);
        eventos.type=ALLEGRO_EVENT_KEY_UP;
    }
    else if(eventos.type==ALLEGRO_EVENT_DISPLAY_CLOSE)
    {
        devuelve=M_ERROR;
    }
    else if(eventos.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN&&is_printign_a_stage()!=M_TRUE)
    {
        print_a_button(cuadrante(eventos.mouse.x,eventos.mouse.y),M_TRUE);
        eventos.type=ALLEGRO_EVENT_KEY_UP;
    }
    return devuelve;
}

//cuadrante
//recive: cordenadas x e y
//devuelve: el numero de cuadrante
uint8_t cuadrante (int16_t x,int16_t y)
{
    uint8_t resultado=M_FALSE;
    if((x<=(P_ANCHO/2))&&(y<=(P_ALTO/2)))
    {
        resultado=PRIMER_CUADRANTE;
    }
    else if ((x>=(P_ANCHO/2))&&(y<(P_ALTO/2)))
    {
        resultado=SEGUNDO_CUADRANTE;
    }
    else if ((x>(P_ANCHO/2))&&(y>(P_ALTO/2)))
    {
        resultado=TERCER_CUADRANTE;
    }
    else if ((x<=(P_ANCHO/2))&&(y>=(P_ALTO/2)))
    {
        resultado=CUARTO_CUADRANTE;
    }
    return resultado;
}

#endif//**************ALEGRO*****************


#ifdef RPI_MODE
#include <wiringPi.h>
#include <unistd.h>
//****defines correspondientes a los gpios
#define BOTON_ROJO 0 
#define BOTON_VERDE 4
#define BOTON_AZUL 6
#define BOTON_AMARILLO 3
//*****************************************
#define SLEEP_BOTON 100000

int8_t inicializar_input(void)
{
     wiringPiSetup () ;
     pinMode (BOTON_ROJO, INPUT);//boton led rojo
     pinMode (BOTON_VERDE, INPUT);//boton led verde
     pinMode (BOTON_AZUL, INPUT);//boton led azul
     pinMode (BOTON_AMARILLO, INPUT);//boton led amarillo
    
}


//get_boton
//recive:nada
//devuelve:el boton presionado. un numero entre 1 y 4
//accion: prende el led del boton presionado
//
int8_t get_boton (void)
{   
    int8_t devuelve=M_FALSE;
    static uint8_t b_rojo=M_FALSE;
    static uint8_t b_verde=M_FALSE;
    static uint8_t b_azul=M_FALSE;
    static uint8_t b_amarillo=M_FALSE;
    
    if(is_printign_a_stage()!=M_TRUE)
    {
    
        if (digitalRead(BOTON_ROJO)==M_FALSE)//rojo
        {
            print_a_button(1,M_TRUE);//LED ROJO
            b_rojo=M_TRUE;
            devuelve=M_FALSE;
            usleep(SLEEP_BOTON);
        }
        else if(b_rojo)
        {
            print_a_button(1,M_FALSE);//LED ROJO
            b_rojo=M_FALSE;
            devuelve=1;
        }
        else if (digitalRead(BOTON_VERDE)==M_FALSE)//verde
        {
            print_a_button(2,M_TRUE);//LED verde
            b_verde=M_TRUE;
            devuelve=M_FALSE;
            usleep(SLEEP_BOTON);
        }
        else if(b_verde)
        {
            print_a_button(2,M_FALSE);//LED verde
            b_verde=M_FALSE;
            devuelve=2;
        }
    
        else if (digitalRead(BOTON_AZUL)==M_FALSE)//boton azul
        {
            print_a_button(3,M_TRUE);//LED azul
            b_azul=M_TRUE;
            devuelve=M_FALSE;
            usleep(SLEEP_BOTON);
        }
        else if(b_azul)
        {
            print_a_button(3,M_FALSE);//LED azul
            b_azul=M_FALSE;
            devuelve=3;
        }
        else if (digitalRead(BOTON_AMARILLO)==M_FALSE)// led amarillo
        {
            print_a_button(4,M_TRUE);//LED ROJO
            b_amarillo=M_TRUE;
            devuelve=M_FALSE;
            usleep(SLEEP_BOTON);
        }
        else if(b_amarillo)
        {
            print_a_button(4,M_FALSE);//LED ROJO
            b_amarillo=M_FALSE;
            devuelve=4;
        }
        else
        {
            devuelve=M_FALSE;
        }
    
    }
    
    return devuelve;
    
}
#endif