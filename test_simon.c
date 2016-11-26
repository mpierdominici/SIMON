#include <stdio.h>
#include <time.h>
#include "simon.h"
#define SIZE_SIMON 3
int main(void)

{
	create_simon(SIZE_SIMON);
	generate_game_simon();
	uint8_t * simon=get_simon();
	int i;
	char c;
	for (i = 0; i <SIZE_SIMON; ++i)
	{
		printf("%d\n",simon[i]);
	}
	while((c=getchar())!='q')
	{
		if (c!='\n')
		{
		c=c-'0';
		c=play_simon(c);
		switch (c)
		{
			case OK:
			printf("%s\n","ok");
			break;
			case GAME_OVER:
			printf("%s\n","game over");
			break;
			case WIN:
			printf("%s\n","WIN");
			break;
			case NEXT_PRINT:
			printf("%s\n","NEXT_PRINT");
			break;

		}
	}
	}
	
	destroy_simon();
}