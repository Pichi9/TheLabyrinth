#ifndef TSCREEN_H
#define TSCREEN_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>
#include <time.h>
#include "../constantes.h"
#include "Map/map.h"
#include "Player/player.h"
#include "Render/render.h"

// Fonction qui affiche l'image de fin en cas de défaite
void endImageLoose(SDL_Renderer *renderer, const char *image);

// Fonction qui affiche l'image de début (chargement)
void startImage(SDL_Renderer *renderer, const char *image);

// Fonction qui affiche l'image de fin en cas de victoire avec un zoom vers la porte de sortie
void endImageWin(SDL_Renderer *renderer, const char *image, int zoom);

// Fonction qui crée un fichier score
void createScore(const char *filename,const char* nom, int beginTime, int endTime);

// Fonction qui récupère le temps restant
int getTimeLeft(int beginTime,int endTime);

// Fonction qui ferme la police
void freeFont(TTF_Font* font);

// Fonction qui applique le texte à l'écran
void applyText(SDL_Renderer *renderer, int x, int y, int w, int h, const char* text, TTF_Font *font);



#endif