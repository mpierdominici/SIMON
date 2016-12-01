#include "print.h"
#include <pthread.h>
#include "pin.h"


    int main(void)
    {
        int i;
        pthread_t ledoutput;
        
        MPIN pines []=
        {
            
            {"4","/sys/class/gpio/gpio4/direction","/sys/class/gpio/gpio4/value"},
            {"17",DIRECTION_P2(17),VALUE_P2(17)},
            {"18",DIRECTION_P2(18),VALUE_P2(18)},
            {"27",DIRECTION_P2(27),VALUE_P2(27)}
            
            
        };
        
        set_gpio(pines);
        
        for (i=0;i<4;i++)
        {
        export_gpio(i);
        direction_gpio(M_OUTPUT ,i);
        value_gpio(M_LOW,i);
        }
        
        //juego (pines);
        
        pthread_create(&ledoutput, NULL, thread, NULL);
        pthread_join(ledoutput, NULL);
     
        for (i=0;i<4;i++)
            unexport_gpio(i);
        
        return 0;
    }



/*
ESTO ES PARA INPUT, PARECIDO A OUTPUT

#include <stdio.h>

#include "print.h"
#include <pthread.h>
#include "pin.h"


int main(void)
{
    int i;
    pthread_t ledoutput;
    
    MPIN pinesin []=
    {
        
        {"4","/sys/class/gpio/gpio4/direction","/sys/class/gpio/gpio4/value"},
        {"17",DIRECTION_P2(17),VALUE_P2(17)},
        {"18",DIRECTION_P2(18),VALUE_P2(18)},
        {"27",DIRECTION_P2(27),VALUE_P2(27)}
        
        
    };
    
    set_gpio(pinesin);
    
    for (i=0;i<4;i++)
    {
        export_gpio(i);
        direction_gpio(M_INPUT ,i);
    }
    
    // no se donde guardar los valores pero aca se llamaria a la funcion que lo lea
    // se llama read_value DEVULEVE: CHAR *
    
    
    for (i=0;i<4;i++)
        unexport_gpio(i);
    
    return 0;
}
*/
