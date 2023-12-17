#ifndef TSCREEN_H
#define TSCREEN_H

#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../constantes.h"
#include "../Map/map.h"
#include "../Player/player.h"
#include "../Render/render.h"


// Fonction qui met une pause
void pause(int time);

// Fonction qui affiche l'image de fin en cas de défaite
void endImageLoose(SDL_Renderer *renderer, const char *image);

// Fonction qui affiche l'image de début (chargement)
void startImage(SDL_Renderer *renderer, const char *image);

// Fonction qui affiche l'image de fin en cas de victoire avec un zoom vers la porte de sortie
void endImageWin(SDL_Renderer *renderer, const char *image, int zoom);

// Fonction qui ajoute du son





#endif