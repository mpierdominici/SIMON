#include <stdio.h> 
#include "t1pin.h"
#include "pin.h"
#include <stdint.h>
static MPIN * m_pines =NULL;

void set_gpio(MPIN * gpio_pines)
{
	m_pines=gpio_pines;
}

int16_t export_gpio(int8_t npin)
{
	FILE * gpiof=NULL;
	int16_t error=0;


	if((gpiof = fopen(EXPORT_P,"w"))==NULL)
	{
		printf("No se pudo abrir el archivo\n");
		error=M_ERROR;
	}

	error = fputs(m_pines[npin].gpio_num,gpiof);

	if(error== M_ERROR)
	{
		printf("no se pudo exportar el pin %s",m_pines[npin].gpio_num);
		error=M_ERROR;
	}
	else
	{
		printf("se exporto correctamente el pin %s",m_pines[npin].gpio_num);
	}
	fclose(gpiof);
	return(error);
}


int16_t unexport_gpio(int8_t npin)
{
	FILE * gpiof=NULL;
	int16_t error=0;


	if((gpiof = fopen(UNEXPORT_P,"w"))==NULL)
	{
		printf("No se pudo abrir el archivo\n");
		error=M_ERROR;
	}

	error = fputs(m_pines[npin].gpio_num,gpiof);

	if(error== M_ERROR)
	{
		printf("no se pudo desexportar el pin %s",m_pines[npin].gpio_num);
		error=M_ERROR;
	}
	else
	{
		printf("se desexporto correctamente el pin %s",m_pines[npin].gpio_num);
	}
	fclose(gpiof);
	return(error);
}

int16_t direction_gpio(int8_t direction ,int8_t npin)
{
	FILE * gpiof=NULL;
	int16_t error=0;


	if((gpiof = fopen(m_pines[npin].mdirection,"w"))==NULL)
	{
		printf("No se pudo abrir el archivo\n");
		error=M_ERROR;
	}
	if(direction==M_INPUT)
	{
		error = fputs("in",gpiof);
	}
	else if(direction==M_OUTPUT)
	{
		error = fputs("out",gpiof);
	}
	

	if(error== M_ERROR)
	{
		printf("no se pudo direccionar el pin %s",m_pines[npin].gpio_num);
		error=M_ERROR;
	}
	else
	{
		//printf("se exporto correctamente el pin %s",m_pines[npin].gpio_num);
	}
	fclose(gpiof);
	return(error);
}

int16_t value_gpio(int8_t value ,int8_t npin)
{
	FILE * gpiof=NULL;
	int16_t error=0;


	if((gpiof = fopen(m_pines[npin].mvalue,"w"))==NULL)
	{
		printf("No se pudo abrir el archivo\n");
		error=M_ERROR;
	}
	if(value==M_HIGH)
	{
		error = fputs("1",gpiof);
	}
	else if(value==M_LOW)
	{
		error = fputs("0",gpiof);
	}
	

	if(error== M_ERROR)
	{
		printf("no se pudo ASIGNAR VALOR el pin %s",m_pines[npin].gpio_num);
		error=M_ERROR;
	}
	else
	{
		//printf("se exporto correctamente el pin %s",m_pines[npin].gpio_num);
	}
	fclose(gpiof);
	return(error);
}