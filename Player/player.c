#include "player.h"



void initPlayer(Player *p)
{
	p->angle = 0.0;
	p->x = 3.0;
	p->y = 3.0;
	p->dx = cos(p->angle);
	p->dy = sin(p->angle);
}


void freePlayer(Player *p)
{
	free(p);
}

void anglePlayer(Player *p)
{
	if (/* condition */)
	{
		/* code */
	}
}