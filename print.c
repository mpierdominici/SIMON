/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <stdlib.h>
#include "boole.h"
#include <stdint.h>
static uint8_t estado_botones[4]={0,0,0,0};

#ifndef RPI_MODE
#include  <allegro5/allegro.h>
#define P_ANCHO 603
#define P_ALTO 603
#include <time.h>
int8_t iniciar_alegro(void);
int8_t iniciar_variables_allegro(void);
void clear_pantalla(void);
void show_changes (void);
void destroy_print (void);
void setear_botones_imprimir(void);
void print_botones(void);
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

int8_t iniciar_variables_allegro(void) 
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


void clear_pantalla(void)
{
   al_set_target_bitmap(al_get_backbuffer(pantalla));
   al_clear_to_color(al_map_rgb(255,255,255));
   al_draw_bitmap(fondo, 0, 0, 0); 
}
void show_changes (void)
{
    al_set_target_bitmap(al_get_backbuffer(pantalla));
    al_flip_display();  
}

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

void print_botones(void){
    uint8_t counter=M_FALSE;
    clear_pantalla();
    for (counter=M_FALSE;counter<4;counter++)
    {
        if(estado_botones[counter]!=M_FALSE)
        al_draw_bitmap((posiciones_botones[counter]).boton,(posiciones_botones[counter]).x,(posiciones_botones[counter]).y, 0);
    }
    al_draw_bitmap(circulo,170,170,0);
    show_changes ();
}

void setear_botones_imprimir(void)
{
    (posiciones_botones[0]).boton=boton_rojo;
    (posiciones_botones[1]).boton=boton_verde;
    (posiciones_botones[2]).boton=boton_azul;
    (posiciones_botones[3]).boton=boton_amarillo;
}

int main(void)
{
    if((iniciar_alegro()==M_ERROR)||(iniciar_variables_allegro()==M_ERROR)){
        return 0;
    }
    clear_pantalla();
    show_changes();
    setear_botones_imprimir();
    char counter=0;
    while (1)
    {
        
        if (counter==4)
        {
            counter=0;
        }
        estado_botones[0]=0;
        estado_botones[1]=0;
        estado_botones[2]=0;
        estado_botones[3]=0;
        
        estado_botones[counter]=1;
        print_botones();
        counter++;
        sleep(1);
    }
    destroy_print();
}

#endif