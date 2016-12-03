
#include "mprint.h"


static MPIN * m_pines =NULL;
static char estado_botones []={1,1,1,1};

void set_gpio(MPIN * gpio_pines)
{
    m_pines=gpio_pines;
}

int export_gpio(char npin)
{
    FILE * gpiof=NULL;
    int error=0;
    
    
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


int unexport_gpio(char npin)
{
    FILE * gpiof=NULL;
    int error=0;
    
    
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

int direction_gpio(char direction ,char npin)
{
    FILE * gpiof=NULL;
    int error=0;
    
    
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

int value_gpio(char value ,char npin)
{
    FILE * gpiof=NULL;
    int error=0;
    
    
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



void * thread (void * v)
{
    FILE * pin_value =NULL;
    int i;
    
    while (1)
    {
     
        for (i=0; i < 4; i++)
            {
                if (estado_botones[i]==M_FALSE)
                {
                    value_gpio(M_LOW,i);
                }
                else
                {
                    value_gpio(M_HIGH,i);
                }
            
                fclose(pin_value);
            }
         
     }
     
 }

void change_led_state (char state, char i)
{
    estado_botones[i]= state;
}
     

/*

boludeo con los leds 
#include <unistd.h>
void juego (MPIN pines [])
{
    int i;
    for (i = 0; i <4; i++)
    {
        value_gpio(M_HIGH, i);
        usleep (200);
        value_gpio(M_LOW, i);
        
    }
    
    for (i = 0; i <4; i++)
    {
        value_gpio(M_HIGH, i);
        usleep(100);
    }
    
    for (i = 0; i <4; i++)
    {
        value_gpio(M_LOW, i);
        usleep(100);
    }
    
    
}
*/

char * read_value (char npin)
{
    FILE * pin_value=NULL;
    char str[2];
    char * value = NULL;
    
   if ((pin_value = fopen( m_pines[npin].mvalue , "r"))==NULL)
    {
        value = NULL;
        printf ("Error opening file");
    }
    
    else
    {
        if ((value = fgets (str,2, pin_value))==NULL)
        {
             printf ("Error reading file");
        }
    }

    fclose(pin_value);
    return value;
}

