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
}


Labyrendu* createrender()
{
    Labyrendu* labyrenderer = calloc(1, sizeof(Labyrendu));
    if (labyrenderer == NULL) 
    {
        printf("Erreur dans l'allocation pour le rendu\n");
        return NULL;   
    }

    labyrenderer->window = SDL_CreateWindow("Le Labyrinthe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    if (labyrenderer->window == NULL) {
        printf("Erreur dans la création de la fenêtre : %s\n", SDL_GetError());
        free(labyrenderer);
        return NULL;
    }

    labyrenderer->renderer = SDL_CreateRenderer(labyrenderer->window, -1, SDL_RENDERER_SOFTWARE);
    if (labyrenderer->renderer == NULL) {
        printf("Erreur de création du rendu : %s\n", SDL_GetError());
        SDL_DestroyWindow(labyrenderer->window);
        free(labyrenderer);
        return NULL;
    }
    return labyrenderer;
}


void initTextures(Labyrendu* labyrenderer)
{
    SDL_Texture* textureFloor = SDL_LoadBMP("../Textures/Floor.bmp");
    SDL_Texture* textureSky = SDL_LoadBMP("../Textures/Sky.bmp");
    SDL_Texture* textureWall = SDL_LoadBMP("../Textures/Wall.bmp");
}


void cleanSDL(SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}