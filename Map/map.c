#include "map.h"


GameMap* CreateMap(const char *filename)
{
	GameMap *map = (GameMap*) malloc(sizeof(GameMap));
	if (map == NULL)
	{
		printf("Erreur dans l'allocation de mémoire pour la carte");
		return NULL;
	}
	FILE *file = fopen(filename,"r");
	if (file == NULL)
	{
		printf("Erreur dans le chargement de la carte");
		free(map);
		return NULL;
	}
	for (int i = 0; i < MAP_HEIGHT;	i++)
	{
		for (int j = 0; i < MAP_WIDTH; j++)
		{
			fscanf(file,"%d",&map->map[i][j]);
		}
	}
	fclose(file);
	return map;
}

void freeMap(GameMap *map)
{
	free(map);
}

