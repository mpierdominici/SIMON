#ifndef PIN_H
#define PIN_H

#define EXPORT_P ("/sys/class/gpio/export")
#define UNEXPORT_P ("/sys/class/gpio/unexport")
#define VALUE_P1(n) ("/sys/class/gpio/gpio"#n"/value")
#define VALUE_P2(n) VALUE_P1(n)
#define DIRECTION_P1(n) ("/sys/class/gpio/gpio"#n"/direction")
#define DIRECTION_P2(n) DIRECTION_P1(n)


typedef struct
{
    char * gpio_num;
    char * mdirection;
    char * mvalue;
    
    
}MPIN;

#endif /* PIN_H */
