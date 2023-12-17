#include "player.h"

void initSpawnCoords(Player *p, GameMap *m){

	int x;
	int y;
	for(int i=0;i<MAP_HEIGHT;i++)
	{
		for(int j=0;j<MAP_WIDTH;j++)
		{
			if(m->map[i][j]==2)
			{
				p->x = j+0.5; // On initialise la position (x) du joueur
				p->y = i+0.5; // On initialise la position (y) du joueur
			}
		}
	}
}

void fixDir(Player *p)
{
	p->dirX = cos(p->angle); // On converti l'angle en radian
	p->dirY = sin(p->angle); // On converti l'angle en radian
}

void initPlayer(Player *p, GameMap *m)
{
 	p->angle = 0.0; // On initialise l'angle du joueur
	initSpawnCoords(p,m);
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