#include "map.h"


GameMap* CreateMap(const char *filename) 
{
    GameMap *map = (GameMap*)malloc(sizeof(GameMap)); // Allocation de la mémoire nécessaire pour la structure GameMap
    if (map == NULL) 
	{
        printf("Erreur dans l'allocation de mémoire pour la carte"); // Gestion des erreurs
        return NULL;
    }

    FILE *file = fopen(filename, "r"); // On ouvre le fichier pour lire la map
    if (file == NULL) 
	{
        printf("Erreur dans le chargement de la carte"); // Gestion des erreurs
        free(map);
        return NULL;
    }
    
    int ligne = 0; // On initialise une variable qui lit la map en ligne
    int coll = 0; // On initialise une variable qui lit la map en colonne
    char c;
    while ((c = fgetc(file)) != EOF) // Lecture de chaque caractère du fichier ligne par ligne et colonne par colonne jusqu'a la fin
	{
        if (c == '0' || c == '1' || c == '2' || c == '9') 
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
    fclose(file); // On ferme le fichier map.txt
    return map;
}


void freeMap(GameMap *map)
{
	free(map); // On libère la mémoire occupé par la structure GameMap
}


int isWall(GameMap *map, int x, int y)
{
	if ((x < 0) || (x >= MAP_WIDTH) || (y < 0) || (y >= MAP_HEIGHT))
	{
		return 1; // Retourne 1 si la position testée correspond à celle d'un mur 
	}
	return map->map[y][x] == 1; // Vérifie justement si c'est un mur
}


int end(GameMap *map, int x, int y)
{
    return map->map[y][x] == 9; // Détermine la position de la fin
}

