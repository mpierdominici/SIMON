/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <stdlib.h>
#include "boole.h"
#include "print.h"
#include <unistd.h>
#define TIEMPO_IMPREESION_STAGE 0.5

static uint8_t estado_botones[4]={0,0,0,0};
static int8_t stop_printing_thread =M_FALSE;
static uint8_t * arreglo_secueencia_simon=NULL;
static uint8_t stage_simon_printing;
static uint8_t stop_thread=M_TRUE;
static uint8_t quit_stand_by=M_FALSE;
#ifndef RPI_MODE
//compilacion para allegro
#include  <allegro5/allegro.h>
#include <time.h>
#define P_ANCHO 603
#define P_ALTO 603
#define FPS 60

void clear_pantalla(void);
void show_changes (void);
void destroy_print (void);


static ALLEGRO_BITMAP * fondo=NULL;
static ALLEGRO_BITMAP * boton_rojo=NULL;
static ALLEGRO_BITMAP * boton_verde=NULL;
static ALLEGRO_BITMAP * boton_amarillo=NULL;
static ALLEGRO_BITMAP * boton_azul=NULL;
static ALLEGRO_BITMAP * circulo=NULL;
static ALLEGRO_DISPLAY * pantalla=NULL;


typedef struct{
    ALLEGRO_BITMAP * boton;
    uint16_t x;
    uint16_t y;
    
}BOTONES_ALLEGRO;

BOTONES_ALLEGRO posiciones_botones[4]={{NULL,38,38},{NULL,319,37},{NULL,319,320},{NULL,38,320}};

//iniciar_allegro
//recive:nada
//devuelve: M_ERROR si no se iicializo satisfatoriamente
//allegro
//
//
int8_t iniciar_alegro(void)
{
    if(!al_init()) {
        fprintf(stderr, "error al inicializar alegro\n"); //evaluo si se inicio correctamente alegro
        return M_ERROR;
        }
    
     if(! al_init_image_addon()) {
      fprintf(stderr, "error al inicializar addon imagenes\n");//evaluo si se pudo iniciar el teclado
      return M_ERROR;
   }

    
    
    return M_TRUE;
    
}

//iniciar_variables_print_allegro
//recive: nada
//devuelve:M_ERROR si no sepudo iniciar las variables necesarias par la ejecuacion de la parte grafica
//accion:inicializa las variables de alegro.
//
int8_t iniciar_variables_print_allegro(void) 
{

if(iniciar_alegro()==M_ERROR)
    {
        return M_ERROR;
    }
    
    
   fondo = al_load_bitmap("simon_display.png");
 
   if(!fondo) {
      fprintf(stderr, "error al abrir la imagen\n");
      return M_ERROR;
   }   
    
 circulo = al_load_bitmap("simon_centro.png");
    if(!circulo) {
      fprintf(stderr, "error al abrir la imagen\n");
      al_destroy_bitmap(circulo);
      return M_ERROR;
   }
 boton_rojo= al_load_bitmap("simon_b_rojo.png");
    if(!boton_rojo) {
      fprintf(stderr, "error al abrir la imagen\n");
      al_destroy_bitmap(fondo);
      al_destroy_bitmap(circulo);
      return M_ERROR;
   }
 boton_verde= al_load_bitmap("simon_b_verde.png");
    if(!boton_verde) {
      fprintf(stderr, "error al abrir la imagen\n");
      al_destroy_bitmap(fondo);
      al_destroy_bitmap(circulo);
      al_destroy_bitmap(boton_rojo);
      al_destroy_bitmap(boton_azul);
      return M_ERROR;
   }
 boton_amarillo= al_load_bitmap("simon_b_amarillo.png");
    if(!boton_amarillo) {
      fprintf(stderr, "error al abrir la imagen\n");
      al_destroy_bitmap(fondo);
      al_destroy_bitmap(circulo);
      al_destroy_bitmap(boton_rojo);
      al_destroy_bitmap(boton_verde);
      al_destroy_bitmap(boton_azul);
      
      return M_ERROR;
   }
 boton_azul= al_load_bitmap("simon_b_azul.png");
    if(!boton_azul) {
      fprintf(stderr, "error al abrir la imagen\n");
      al_destroy_bitmap(fondo);
      al_destroy_bitmap(circulo);
      al_destroy_bitmap(boton_rojo);
      al_destroy_bitmap(boton_verde);
      al_destroy_bitmap(boton_amarillo);
      return M_ERROR;
   }
 
 pantalla = al_create_display(P_ANCHO,P_ALTO);
    if(!pantalla) {
        fprintf(stderr, "error al crear la pantalla\n");
     
      al_destroy_bitmap(fondo);
      al_destroy_bitmap(circulo);
      al_destroy_bitmap(boton_rojo);
      al_destroy_bitmap(boton_verde);
      al_destroy_bitmap(boton_azul);
      al_destroy_bitmap(boton_amarillo);
        return M_ERROR;
        }
 }


//clear_pantalla
//recive:devuelve:nada
//accion:setea el backbuffer de la pantalla unicamente con la imagen que se selecciono
//para el fondo. para que se vean los cambios se deve ejecutar show_changes
//
void clear_pantalla(void)
{
   al_set_target_bitmap(al_get_backbuffer(pantalla));
   al_clear_to_color(al_map_rgb(255,255,255));
   al_draw_bitmap(fondo, 0, 0, 0); 
}

//show_changes
//recive:devuelve:nada
//accion:pone en pantalle lo que havia en el backbuffer de la pantalla
//
void show_changes (void)
{
    al_set_target_bitmap(al_get_backbuffer(pantalla));
    al_flip_display();  
}

//destroy_print
//recive:devuelve:nada
//accion: desreserva las memoria utilizada para las variables de allegro
//
//
void destroy_print (void)
{
      al_destroy_bitmap(fondo);
      al_destroy_bitmap(circulo);
      al_destroy_bitmap(boton_rojo);
      al_destroy_bitmap(boton_verde);
      al_destroy_bitmap(boton_azul);
      al_destroy_bitmap(boton_amarillo);
      al_destroy_display(pantalla);
}

//print_botones
//recive:devuelve:nada
//accion: imprime el color correspondiente a cada boton del simon,
//si no hay M_FALSE en la posicion, del arreglo estado_botones, correspondiente
//a cada boton
void * print_botones(void * A){
    stop_thread=M_TRUE;
    while(stop_thread)
    {
    uint8_t counter=M_FALSE;
    counter=M_FALSE;
    clear_pantalla();
    for (counter=M_FALSE;counter<4;counter++)
    {
        if(estado_botones[counter]!=M_FALSE)
        al_draw_bitmap((posiciones_botones[counter]).boton,(posiciones_botones[counter]).x,(posiciones_botones[counter]).y, 0);
    }
    al_draw_bitmap(circulo,170,170,0);
    show_changes ();
    }
}

//setear_botones_imprimir
//recive:devuelve:nada
//accion:prepara la imagen de los botones del simon
//nota:se deve ejecutar entes que print_botones
//
//
void setear_botones_imprimir(void)
{
    (posiciones_botones[0]).boton=boton_rojo;
    (posiciones_botones[1]).boton=boton_verde;
    (posiciones_botones[2]).boton=boton_azul;
    (posiciones_botones[3]).boton=boton_amarillo;
}

void * get_siplay(void)
{
    return ((void*)pantalla);
}

#endif

//set_print-stage_simon
//recive: arreglo con la secuencia de juego, y cuanto de esa secuencia deve imprimirse
//devuelve:nada
//accion: permite imprimir secuencia de numeros
//
//
void set_print_stage_simon(uint8_t * arreglo_de_secuencias,uint8_t stage_simon)
{
    arreglo_secueencia_simon=arreglo_de_secuencias;
    stage_simon_printing=stage_simon;
}

//print_stage_simon
//recive:devuelve:nada
//accion: imprime la secuencai de juego hasta donde se inidque,a travez de set_print_stage_simon
//
//
void * print_stage_simon(void * v)
{
    uint8_t counter=M_FALSE;
   stop_printing_thread=M_TRUE;
    for(counter=M_FALSE;counter<stage_simon_printing;counter++)
    {
        uint8_t black_out;
        for (black_out=M_FALSE;black_out<4;black_out++)
        {
            estado_botones[black_out]=M_FALSE;
        }
    
        usleep(500000);
        estado_botones[(arreglo_secueencia_simon[counter])-1]=M_TRUE;
        usleep(500000);
        estado_botones[(arreglo_secueencia_simon[counter]-1)]=M_FALSE;
    }
   
   stop_printing_thread=M_FALSE;
}

//stop_all_thread
//recive:devuelve:nada
//accion: detiene los thread, de impresion
//
//
void stop_all_thread(void)
{
    stop_thread=M_FALSE;
}
//is_printing_a_stage
//recive:nada;
//devuelve:M_TRUE si se esta imprimiendo un stage
//         M_FALSE si no se esta imprimiendo un stage
//
uint8_t is_printign_a_stage(void)
{
    return stop_printing_thread;
}
//print_a_button 
//recive: el n° de luz que deseamos cambianr de estado, y value, si lo queremos prende o apagar
//devuelve: nada
//
//
void print_a_button(uint8_t nbotton,uint8_t value)
{
    estado_botones[(nbotton-1)]=value;
}
//get_estado_botones
//recive:nada
//devuelve: puntero a char
//

uint8_t * get_estados_botones(void)
{
    return estado_botones;
}

void * stand_by(void * v)
{
    uint8_t counter=M_FALSE;
    quit_stand_by=M_TRUE;
    while (quit_stand_by)
    {
        for(counter=M_FALSE;counter<4;counter++)
        {
            if(!quit_stand_by)
            {
                break;
            }
            estado_botones[counter]=M_TRUE;
            if(!quit_stand_by)
            {
                break;
            }
            sleep(1);
            estado_botones[counter]=M_FALSE;
            if(!quit_stand_by)
            {
                break;
            }
            sleep(1);
            if(!quit_stand_by)
            {
                break;
            }
        }
    }
    for(counter=M_FALSE;counter<4;counter++)
        {
            estado_botones[counter]=M_FALSE;
    }
    
}

void stop_stand_by(void)
{
    quit_stand_by=M_FALSE;
    
}