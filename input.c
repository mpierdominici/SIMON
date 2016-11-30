/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdio.h>

#include <stdlib.h>
#include <allegro5/allegro.h>
#include "boole.h"
#include "input.h"
#include "print.h"
static ALLEGRO_DISPLAY *pantalla =NULL;
static ALLEGRO_EVENT_QUEUE *cola_de_eventos =NULL;
enum{PRIMER_CUADRANTE = 1 ,SEGUNDO_CUADRANTE,TERCER_CUADRANTE,CUARTO_CUADRANTE};
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
//recive:puntero a void. el primero es un puntero a display
//
//
//
void set_input (void * display)
{
   pantalla= (ALLEGRO_DISPLAY *)display;
}

int8_t get_boton (void)
{
    int8_t devuelve=M_FALSE;
    al_get_next_event(cola_de_eventos, &eventos);
    if(eventos.type==ALLEGRO_EVENT_MOUSE_BUTTON_UP)
    {
        devuelve=cuadrante(eventos.mouse.x,eventos.mouse.y);
        eventos.type=ALLEGRO_EVENT_KEY_UP;
    }
    else if(eventos.type==ALLEGRO_EVENT_DISPLAY_CLOSE)
    {
        devuelve=M_ERROR;
    }
    return devuelve;
}

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