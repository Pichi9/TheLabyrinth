#include "map.h"


GameMap* CreateMap(const char *filename) 
{
    GameMap *map = (GameMap*)malloc(sizeof(GameMap));
    if (map == NULL) 
	{
        printf("Erreur dans l'allocation de mémoire pour la carte");
        return NULL;
    }

    FILE *file = fopen(filename, "r");
    if (file == NULL) 
	{
        printf("Erreur dans le chargement de la carte");
        free(map);
        return NULL;
    }
    
    int ligne = 0;
    int coll = 0;
    char c;
    while ((c = fgetc(file)) != EOF) 
	{
        if (c == '0' || c == '1') 
		{
            map->map[ligne][coll] = c - '0';
            coll++;
            if (coll == MAP_WIDTH) 
			{
                coll = 0;
                ligne++;
            }
            if (ligne == MAP_HEIGHT) 
			{
                break;
            }
        }
    }
    fclose(file);
    return map;
}


void freeMap(GameMap *map)
{
	free(map);
}


int isWall(GameMap *map, int x, int y)
{
	if ((x < 0) || (x >= MAP_WIDTH) || (y < 0) || (y >= MAP_HEIGHT))
	{
		return 1;
	}
	return map->map[y][x] == 1;
}


void printMap(GameMap *map)
{
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			printf("%d", map->map[i][j]);
		}
		printf("\n");
	}
}

int end(); // Fonction a finir


