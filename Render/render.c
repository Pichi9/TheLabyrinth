#include "render.h"

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
    labyrenderer->textureFloor = SDL_CreateTextureFromSurface(labyrenderert->render,textureFloor);
    SDL_Texture* textureSky = SDL_LoadBMP("../Textures/Sky.bmp");
    labyrenderer->textureSky = SDL_CreateTextureFromSurface(labyrenderert->render,textureSky);
    SDL_Texture* textureWall = SDL_LoadBMP("../Textures/Wall.bmp");
    labyrenderer->textureWall = SDL_CreateTextureFromSurface(labyrenderert->render,textureWall);
}

void initRect(Labyrendu* labyrenderer,int x,int y,int w,int h){
    SDL_Rect a = {x,y,w,h};
    SDL_RenderFillRect(labyrender->renderer, &a);
}

void renderFloor(Labyrendu* labyrenderer){
    SDL_Rect a = {0.0,0.0,max,max};
    SDL_Rect b = {0.0,SCREEN_HEIGHT/2,SCREEN_WIDTH,SCREEN_HEIGHT/2};

    SDL_RenderCopy(labyrenderer->renderer,labyrenderer->textureFloor,&a,&b)
}

void renderSky(Labyrendu* labyrenderer){
    SDL_Rect a = {0.0,0.0,max,max};
    SDL_Rect b = {0.0,0.0,SCREEN_WIDTH,SCREEN_HEIGHT/2};

    SDL_RenderCopy(labyrenderer->renderer,labyrenderer->textureSky,&a,&b)
}

void renderAll(Labyrendu* labyrender){
    renderFloor(labyrender);
    renderSky(labyrender);
}

void cleanSDL(SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


