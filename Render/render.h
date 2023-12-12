#ifndef RENDER_H
#define RENDER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../constantes.h"
#include "../Map/map.h"
#include "../Player/player.h"


typedef struct 
{
    SDL_Renderer* renderer;
    SDL_Window* window;
    SDL_Texture* textureFloor;
    SDL_Texture* textureWall;
    SDL_Texture* textureSky;
} Labyrendu;


// Fonction qui initialise la SDL 
void initSDL(SDL_Window** window, SDL_Renderer** renderer);

// Fonction qui créer la fenetre et le renderer
Labyrendu* createrender();

// Fonction qui libère toutes les ressources SDL 
void cleanSDL(SDL_Window* window, SDL_Renderer* renderer);

// Fonction qui initialise les textures
void initTextures(Labyrendu* labyrenderer);

// Fonction qui crée un rendu d'un rectangle
void initRect(Labyrendu* labyrenderer,int x,int y,int w,int h);

// Fonction qui crée un rendu du sol
void renderFloor(Labyrendu* labyrenderer);

// Fonction qui crée un rendu du ciel
void renderSky(Labyrendu* labyrenderer);

// Fonction qui crée un rendu des choses statiques
void renderAll(Labyrendu* labyrender);

// Fonction qui crée un rendu des murs
void renderWall(Labyrendu* labyrenderer,GameMap* map, Player* p);






#endif