/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   simon_main.c
 * Author: matias
 *
 * Created on 29 de noviembre de 2016, 13:37
 */

#include <stdio.h>
#include <stdlib.h>
#include  <pthread.h>
#include "print.h"
#include  "simon.h"
#include  "boole.h"
#include "time.h"
#include "input.h"
#define ITERACIONES_SIMON 5
/*
 * 
 */
int main(int argc, char** argv) 
{    
     pthread_t thread_print_botones,print_stage;
    int16_t boton_presionado;
    //void *v;
    if(iniciar_alegro()==M_ERROR||iniciar_variables_print_allegro()==M_ERROR)
    {
        return 0;
    }
    
    setear_botones_imprimir();
    set_input (get_siplay());
    
    
    
    if(inicializar_input()==M_ERROR)
    {
        return 0;
    }
    pthread_create(&thread_print_botones,NULL,print_botones,NULL);
   
    create_simon(ITERACIONES_SIMON);
    generate_game_simon();
    
    set_print_stage_simon(get_simon(),get_stage());
    pthread_create(&print_stage,NULL,print_stage_simon,NULL);
    
    
    while((boton_presionado=get_boton())!=M_ERROR)
    {
        if((boton_presionado!=M_FALSE)&&(is_printign_a_stage()==M_FALSE))
        {
           
            play_simon(boton_presionado);
                    
            
            
            
        }
        
    }
    
    stop_all_thread();
    pthread_join(thread_print_botones,NULL);
    destroy_print();
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