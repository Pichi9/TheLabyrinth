#ifndef RENDER_H
#define RENDER_H

#include <SDL.h>
#include <SDL_image.h>




// Fonction qui initialise la SDL et crée la fenêtre, le rendu
void initSDL(SDL_Window** window, SDL_Renderer** renderer);

// Fonction qui libère toutes les ressources SDL 
void cleanSDL(SDL_Window* window, SDL_Renderer* renderer);

#endif