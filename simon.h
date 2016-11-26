#ifndef SIMON_H
#define SIMON_H

#include <stdint.h>
enum {OK,GAME_OVER,WIN,NEXT_PRINT};
void create_simon(uint16_t n_de_iteraciones);
void destroy_simon(void);
void generate_game_simon(void);
int16_t play_simon(uint8_t n_press);
uint8_t * get_simon(void);

#endif // SIMON_H