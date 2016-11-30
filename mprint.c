#include "print.h"
#include "boole.h"


static char * leds[4] = {"22","23","24","25"};
static uint8_t ledstate [4]={0};

void toggle ( uint8_t led)

{
   if (ledstate [led] == M_FALSE)
   {
       ledstate [led]= M_TRUE;
   }
   else
   {
       ledstate [led]= M_FALSE;
   }
}




void * thread ()
{
    FILE * pin_value =NULL;
    int notwritten2;
    int i;
    
    while (1)
    {
        for (i=0; i < 4; i++)
        {
            if ((pin_value=fopen(GPIO_VALUE2(leds [i]), "w")))
            {
             printf ("ERROR opening the file");
            }
            
            if (ledstate[i]==M_FALSE)
            {
                notwritten2 = fputs("0", pin_value);
            }
            else
            {
                notwritten2 = fputs("1", pin_value);
            }
        
            fclose(pin_value);
        }

    }

}
    
    
    
    
void initiate_out ()
{
    int i;
    FILE * pin_export = NULL;
    FILE * pin_direction = NULL;
    int notwritten;
    
    for (i=0;i<4;i++)
    {
        if ((pin_export = fopen (GPIO_OPEN1, "w"))== NULL)
        {
            printf ("ERROR opening the file");
        }
        
    
        notwritten = fputs ( leds [i], pin_export);
        if (notwritten== M_ERROR)
        {
            printf("ERROR exporting pin");
            
        }
        
        fclose(pin_export);
        
        if ((pin_direction = fopen(GPIO_DIRECTION2(leds [i]), "w"))== NULL)
        {
            printf("ERROR opening pin");
        }
        
        notwritten = fputs("out", pin_direction);
        if ( notwritten== M_ERROR)
        {
            printf("ERROR setting pin as output");
        }
        
        fclose(pin_direction);
        
    }
}

/* ejemplo de main

#include "print.h"
#include <pthread.h>

int main (void)
{
    pthread_t print_led;
    
    initiate_out();
    
    pthread_create(&print_led, NULL, thread, NULL);
    pthread_join(print_led, NULL);
    return 0;
    
}
*/
