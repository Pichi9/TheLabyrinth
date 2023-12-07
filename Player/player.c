#include "player.h"

void fixDir(Player *p){
	p->dirX = cos(p->angle);
	p->dirY = sin(p->angle);
}

void initPlayer(Player *p)
{
 	p->angle = 0.0;
	p->x = 3.0;
	p->y = 3.0;
	fixDir(p);
}


void freePlayer(Player *p)
{
	free(p);
}

void anglePlayer(Player *p)
{
	while(p -> angle < 0){
		p->angle+=2*pi;
	}
	while(p->angle>2*pi){
		p->angle-=2*pi;
	}
	fixDir(p);
}