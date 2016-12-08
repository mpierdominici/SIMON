/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdint.h>
#include "libaudio.h"
#include   "boole.h"
#include  "print.h"
#include  "sound_simon.h"
int8_t * sonido_botones(uint8_t nboton);
enum{ROJO,VERDE,AZUL,AMARILLO};
static uint8_t * state_botones=NULL;
static char boton_RED[]="./Sound/red.wav";
static char boton_GREEN[]="./Sound/green.wav";
static char boton_BLUE[]="./Sound/blue.wav";
static char boton_YELLOW[]="./Sound/yellow.wav";
static char error_BUZZ[]="./Sound/buzz.wav";
static char gane_s[]="./Sound/win.wav";
static uint8_t mute =M_TRUE;
static uint8_t thread_sound=M_TRUE;

void inicializar_sonido(void)
{
    init_sound(); // Init sound driver
}

void set_audio_vars(void)//sincroniza el la impresion en pantalla con el audio
{
   state_botones=get_estados_botones();
}

void * play_sound_button(void * v)
{
    uint8_t last_play=M_FALSE;
    uint8_t counter=M_FALSE;
    thread_sound=M_TRUE;
   
    while (thread_sound){
        if(!mute)
        {
            stop_sound();
        }
    
        else if((state_botones[ROJO]==M_FALSE)&&(state_botones[VERDE]==M_FALSE)&&(state_botones[AZUL]==M_FALSE)&&(state_botones[AMARILLO]==M_FALSE))
    {
        if(player_status()==PLAYING)
        {
           stop_sound(); 
        }
        
    }
    else if(player_status()==PLAYING)
    {
         for(counter=M_FALSE;counter<4;counter++)
         {
             if(state_botones[counter]!=M_FALSE)
             {
                 break;
             }
         }
        if(counter!=last_play)
        {
            last_play=counter;
            stop_sound();
            set_file_to_play(sonido_botones(counter));
            play_sound();
        }
        
    }
    else //if((player_status()==STOPPED)||(player_status()==FINISHED))
    {
          for(counter=M_FALSE;counter<4;counter++)
         {
             if(state_botones[counter]!=M_FALSE)
             {
                 break;
             }
         }
        last_play=counter;
        stop_sound();
        set_file_to_play(sonido_botones(counter));
        play_sound(); 
    }
    
    }
}


int8_t * sonido_botones(uint8_t nboton)
{
    switch(nboton)
    {
        case ROJO:
            //printf("rojo");
            return boton_RED;
            break;
        case VERDE:
           // printf("verde");
            return boton_GREEN;
            break;
        case AZUL:
           // printf("azul");
            return boton_BLUE;
            break;
        default:
           // printf("amarillo");
            return boton_YELLOW;
            break;            
    }
}

void sound_mute (void)
{
    mute=M_FALSE;
}

void sound_unmute(void)
{
    mute=M_TRUE;
}

void perdi(void)
{
     stop_sound();
     set_file_to_play(error_BUZZ);
     play_sound();
}

void gane(void)
{
     stop_sound();
     set_file_to_play(gane_s);
     play_sound();
}

void stop_thread_sound(void)
{
    thread_sound=M_FALSE;
}

