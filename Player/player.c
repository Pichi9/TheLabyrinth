#include "player.h"

void fixDir(Player *p)
{
	p->dirX = cos(p->angle); // On converti l'angle en radian
	p->dirY = sin(p->angle); // On converti l'angle en radian
}

void initPlayer(Player *p)
{
 	p->angle = 0.0; // On initialise l'angle du joueur
	p->x = 3.0; // On initialise la position (x) du joueur
	p->y = 3.0; // On initialise la position (y) du joueur
	fixDir(p); // On met à jour les angles
}

void freePlayer(Player *p)
{
	free(p); // On libère la mémoire occupé par la structure Player
}

void anglePlayer(Player *p)
{
	while(p -> angle < 0)
	{
		p->angle+=2*pi;
	}
	while(p->angle>2*pi)
	{
		p->angle-=2*pi;
	}
	fixDir(p); // On met à jour les angles
}