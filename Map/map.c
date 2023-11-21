#include "map.h"


GameMap* CreateMap(const char *file)
{
	GameMap *map = (GameMap*) malloc(sizeof(GameMap));
	if (map == NULL)
	{
		printf("Erreur dans l'allocation de mémoire pour la carte");
		return NULL;
	}
	FILE *file = fopen(file,"map.txt");
	if (file == NULL)
	{
		printf("Erreur dans le chargement de la carte");
		free(map);
		return NULL;
	}
	for (int i = 0; i < MAP_HEIGHT;	i++)
	{
		for (int i = 0; i < MAP_WIDTH; i++)
		{
			fscanf(file,"%d",&map->map[i][j]);
		}
	}
	fclose(file);
	return map
}

