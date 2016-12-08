
/************************************************************/
/*  Trabajo Practico FINAL SIMON                            */
/*                                                          */
/*                                                          */
/*Integrantes del grupo:                                    */
/*Maspero Martina(57120),Pierdominici Matias(57498),        */
/*Ayouba Gael(58622)                                        */
/*                                                          */
/************************************************************/
//GIT: https://github.com/mpierdominici/SIMON.git


/* modo compilacion rpi: gcc simon_main.c puntaje.c print.c input.c libaudio.c sound_simon.c simon.c -I/usr/local/include -L/usr/local/lib -lSDL -lpthread -lwiringPi
*/
#include <stdio.h>
#include <stdlib.h>
#include  <pthread.h>
#include "print.h"
#include  "simon.h"
#include  "boole.h"
#include "time.h"
#include "input.h"
#include  "sound_simon.h"
#include  "modo_compilacion.h"
#include   "puntaje.h"
#define ITERACIONES_SIMON 5//cantidad de secuencias del simon
/*
 * 
 */
int main(int argc, char** argv) 
{    
    uint8_t stand_by_mode =M_FALSE;//flag para el modo stand by. si esta en M_FALSE entra en modo stand by
    uint8_t first_stage=M_FALSE;//flag para iniciar la partida. si esta en M_FALSE se inicializa lña partdia
    uint8_t counter=M_FALSE;//contador de puntaje
     pthread_t thread_print_botones,print_stage,sound,stand_by_t;//variables para almazenar el id de los thread
    int16_t boton_presionado;
    
    
    //*******************INICIALIZACION**********************************************
#ifdef RPI_MODE
 
 
        
       
        void init_print_led();
        inicializar_input();//evalua si se pudo inicializar correctamenta el imput de allegro
        pthread_create(&thread_print_botones, NULL, thread, NULL);
    
    
#endif
    

#ifndef RPI_MODE
    if(iniciar_alegro()==M_ERROR||iniciar_variables_print_allegro()==M_ERROR)//chequeo si se inicializo correctamente allegro
    {
        return 0;
    }
    
    setear_botones_imprimir();//inicializo los botonoes para ser imprimidos con allegro
    set_input (get_siplay());//se le indica al input de allegro el display de donde leer los clikcs
    
    
    
    if(inicializar_input()==M_ERROR)//evalua si se pudo inicializar correctamenta el imput de allegro
    {
        return 0;
    }
    
    pthread_create(&thread_print_botones,NULL,print_botones,NULL);//inicializo el thread que imprime los botones en pantalla
#endif//*************ALEGRO*********************
    
    //*****************************SIMON***********************************
    
    create_simon(ITERACIONES_SIMON);//genero el tamaño del arreglo de secuencias del simon
    generate_game_simon();//genero la secuencia randomk de numeros
    
    inicializar_sonido();//prepara el sistema para reproducir audio
    set_audio_vars();//sincroniza la imprencion en pantalla con el audio
 
    
    while((boton_presionado=get_boton())!=M_ERROR)//se termina cuando se cirra la pantalla
    {
        if(!stand_by_mode)//se ejecuta una vez, entra en modo stand_by 
        {
            //pthread_create(&sound,NULL,play_sound_button,NULL);//se iunicializa el thread que reproduce audio
            //sound_mute();//se pone en mute al sisteam
            pthread_create(&stand_by_t,NULL,stand_by,NULL);//se inicializa el thread que genera la secuencia de prendido del modo stand by
            stand_by_mode=M_TRUE;//pasa stand by mode a M_TRUE, para que no se vuelva a ejecutar
        }
         if((boton_presionado!=M_FALSE)&&(is_printign_a_stage()==M_FALSE))//si se presiona un boton
        {
            if(!first_stage)//se ejecuta first stage
            {   
                
                stop_stand_by();//detien el thread que imprime la secuencia de stand by
                pthread_join(stand_by_t,NULL);//espera a que se detenga el thread de stand by
                //sound_unmute();//desmutea la rutina de audio
                pthread_create(&sound,NULL,play_sound_button,NULL);
                
                set_print_stage_simon(get_simon(),get_stage());//setea la primer secuencua del juego
                pthread_create(&print_stage,NULL,print_stage_simon,NULL);//imprime la primer secuenacia del juego
                first_stage=M_TRUE;//
                
            }
            
            else
            
            {   
            switch(play_simon(boton_presionado))
            {
                case OK:
                    
                    break;
                case WIN:
                    counter ++;
                    
                    
                    stop_thread_sound();
                    pthread_join(sound,NULL);
                    gane();
                    generate_game_simon();
                    first_stage=M_FALSE;
                    stand_by_mode=M_FALSE;
                    usleep(500000);
                    puntaje((int)counter);
                    counter=M_FALSE;
                    
                    
                    break;
                case GAME_OVER:
                    
                    stop_thread_sound();
                    pthread_join(sound,NULL);
                    perdi();
                    generate_game_simon();
                    first_stage=M_FALSE;
                    stand_by_mode=M_FALSE;
                    usleep(500000);
                    puntaje((int)counter);
                    counter=M_FALSE;
                    break;
                case NEXT_PRINT:
                    counter++;
                    set_print_stage_simon(get_simon(),get_stage());
                    pthread_create(&print_stage,NULL,print_stage_simon,NULL);
                    break;
            }            
            }

                    
            
            
            
        }
        
    }
    
   
    stop_all_thread();
#ifndef RPI_MODE
    pthread_join(thread_print_botones,NULL);
    destroy_print();
#endif

#ifdef RPI_MODE
    end_print();
    
#endif
    return (EXIT_SUCCESS);
}









/*
 int main(int argc, char** argv) {
    pthread_t t1,t2;
    
    if(iniciar_alegro()==M_ERROR||iniciar_variables_print_allegro()==M_ERROR)
    {
        return 0;
    }
    
    setear_botones_imprimir();
    
    
    
    pthread_create(&t1,NULL,print_botones,NULL);
    create_simon(10);
    generate_game_simon();
    
    set_print_stage_simon(get_simon(),4);
    
    print_stage_simon();
    stop_all_thread();
    pthread_join(t1,NULL);
    destroy_print ();    
    
    
    

    return (EXIT_SUCCESS);
}


 */