#include "render.h"
#include <SDL.h>   
#include <SDL_image.h>
#include "../../LeLabyrinthe/constantes.h"


void initSDL(SDL_Window** window, SDL_Renderer** renderer)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("Erreur dans l'initialisation de SDL : %s\n", SDL_GetError());
        return;
    }

    *window = SDL_CreateWindow("Le Labyrinthe", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (*window == NULL)
    {
        printf("Erreur dans la création de la fenêtre : %s\n", SDL_GetError());
        SDL_Quit();
        return;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (*renderer == NULL)
    {
        printf("Erreur de la création du rendu : %s\n", SDL_GetError());
        SDL_DestroyWindow(*window);
        SDL_Quit();
        return;
    }
}

void cleanSDL(SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}