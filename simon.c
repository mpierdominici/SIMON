#include <stdio.h>

#include <stdlib.h>
#include <time.h>
#include "boole.h"
#include "simon.h"
#define MAX_NUMBER 4//maximo numero generado por generate_game_simon
#define MIN_NUMBER 1//minimo numero generado por el generate_game_simon
#define RANDOM_NUMBER (MIN_NUMBER+(rand()%(MAX_NUMBER)))
#define DEFAULT_ITERATIONS 10
static void emergenci_set_up_simon(void);

static uint8_t * secuencia_de_juego=NULL;
static uint16_t game_iteration=M_FALSE;
static uint16_t stage_game_simon=M_FALSE;



void create_simon(uint16_t n_de_iteraciones)//reserva memoria para el arreglo de secuencias
{
	secuencia_de_juego=(uint8_t *)calloc(n_de_iteraciones,sizeof(uint8_t));
	game_iteration=n_de_iteraciones;
}

static void emergenci_set_up_simon(void)//si no se ejecuta primero create_simon, se crea un arrelgo con un temaño de DEFAULT_ITERATION
{
	create_simon(DEFAULT_ITERATIONS);
	printf("%s\n","no se ha inicializado simon, entonces se inicializo por default" );
}

void destroy_simon(void)//livero el heep
{
	free(secuencia_de_juego);
}

void generate_game_simon(void)//genera aleatoriamente la secuencia de encendido y la guarda en el arreglo
{
	uint8_t counter=M_FALSE;
	if (secuencia_de_juego==NULL || game_iteration==M_FALSE)
	{
		emergenci_set_up_simon();
	}

	
	srand(time(NULL));
	for(counter=M_FALSE;counter<game_iteration;counter++)
	{
		secuencia_de_juego[counter]=RANDOM_NUMBER;
	}
}

int16_t play_simon(uint8_t n_press)
{
	static uint16_t counter_iteration=M_FALSE;

	uint8_t result_simon=GAME_OVER;
	
	if(n_press==secuencia_de_juego[counter_iteration])
	{
		if (counter_iteration==stage_game_simon)//cheque si se llego a la stage correspondiente
		{
			if (stage_game_simon==(game_iteration-1))//chequeo si ya complete todas las iteraciones del juego
			{
				result_simon=WIN;
			}
			else
			{
				stage_game_simon++;
				counter_iteration=M_FALSE;
				result_simon=NEXT_PRINT;
			}
			
		}
		else
		{
			counter_iteration++;
			result_simon=OK;

		}
	}
	else
	{
		result_simon=GAME_OVER;
	}

	return result_simon;
}

uint8_t * get_simon(void)
{
	return secuencia_de_juego;
}