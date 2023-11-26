#ifndef RENDER_H
#define RENDER_H

#include <SDL.h>
#include <SDL_image.h>

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



#endif