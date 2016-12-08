
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "boole.h"
#include "puntaje.h"


int puntaje(int nuevo_puntaje)
{
    int viejo_puntaje;
    FILE * score;
    int mejor_puntaje = 0;
    char str [4];
    int error;
    
    score = fopen ("max.txt", "r");
   
   
    fscanf(score, "%d",&viejo_puntaje);
    fclose(score);
    score = fopen ("max.txt", "w");
    

    if (viejo_puntaje >= nuevo_puntaje)
    {
        mejor_puntaje = viejo_puntaje;
    }
    else 
    {
        mejor_puntaje = nuevo_puntaje;
    }

    sprintf (str,"%d",mejor_puntaje);
    fputs ( str, score);
    fclose(score);
    
    return M_TRUE;
}
