#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "boole.h"
#include "simon.h"
#define MAX_NUMBER 4//maximo numero generado por generate_game_simon
#define MIN_NUMBER 1//minimo numero generado por el generate_game_simon
#define RANDOM_NUMBER (MIN_NUMBER+(rand()%(MAX_NUMBER)))//macro para genera numeros entre MIN_NUMBER Y MAX_NUMBER
#define DEFAULT_ITERATIONS 10

static void emergenci_set_up_simon(void);//funcion que inicializa el simon con DEFAULT_ITERATION

static uint8_t * secuencia_de_juego=NULL;//puntero que almacena los numeros generados aleatoriamente
static uint16_t game_iteration=M_FALSE;//cantidad de numeros aleatorios generados
static uint16_t stage_game_simon=M_FALSE;//contador que indica hasta que parte del juego se llego


//create_simon
//recibe:la cantidad de numeros que el jugador debera memorizar
//devuelve:nada
//accion: reserva memoria equivalente a lo que recibe
//
void create_simon(uint16_t n_de_iteraciones)
{
	secuencia_de_juego=(uint8_t *)calloc(n_de_iteraciones,sizeof(uint8_t));
	game_iteration=n_de_iteraciones;
}


//emergenci_set_up
//recibe=devuelve nada
//accion: esta funcion selecciona DEFAULT_ITERATION, como cantidad de numeros
//que el jugador deve memorizar
//
static void emergenci_set_up_simon(void)//si no se ejecuta primero create_simon, se crea un arrelgo con un temaño de DEFAULT_ITERATION
{
	create_simon(DEFAULT_ITERATIONS);
	printf("%s\n","no se ha inicializado simon, entonces se inicializo por default" );
}


//destroy_simon
//revive = devuelve=nada
//accion: livera el espacio reservado para el juego
//
void destroy_simon(void)//livero el heap
{
	free(secuencia_de_juego);
}


//generate_game_simon
//recibe=devuelve=nada
//accion: la guncion genera aleatoriamente numeros entre 1 y 4, y los almacena en el
//arreglo generado por create_simon. si no se ejecuta create_simon previamente, esta fuancion
//la llamara emergenci_set_up_simon, y lo creara.
//
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

//play_simon
//recibe:la tecla presionada por el usuario
//devuelve: OK(indica que la tecla presionada fue correcta)
//			NEXT_PRINT(indica que ya se presiono correctamente toda una iteracion del simon)
//			WIN(indica que se gano el juego)
//			GAME_OVER(indica que presiono la tecla erronea)
//
//

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
				stage_game_simon=M_FALSE;
				counter_iteration=M_FALSE;
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
		stage_game_simon=M_FALSE;
		counter_iteration=M_FALSE;
	}

	return result_simon;
}

//get_simon
//recibe: nada
//devuelve: puntero al arreglo donde se almacenan las secuencias de juego
//
uint8_t * get_simon(void)
{
	return secuencia_de_juego;
}
