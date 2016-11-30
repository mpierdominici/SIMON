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
/*
 * 
 */
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
    
    set_print_stage_simon(get_simon(),3);
    
    print_stage_simon();
    stop_all_thread();
    destroy_print ();    
    
    
    

    return (EXIT_SUCCESS);
}

