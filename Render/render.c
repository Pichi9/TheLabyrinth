#include "render.h"

void initSDL()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("Erreur dans l'initialisation de SDL : %s\n", SDL_GetError());
        return;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) 
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
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
    SDL_Surface* tempSurface;
    tempSurface = SDL_LoadBMP("Ressources/Textures/Floor.bmp");
    labyrenderer->textureFloor = SDL_CreateTextureFromSurface(labyrenderer->renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    tempSurface = SDL_LoadBMP("Ressources/Textures/Sky.bmp");
    labyrenderer->textureSky = SDL_CreateTextureFromSurface(labyrenderer->renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    tempSurface = SDL_LoadBMP("Ressources/Textures/Wall.bmp");
    labyrenderer->textureWall = SDL_CreateTextureFromSurface(labyrenderer->renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
}

void initRect(Labyrendu* labyrenderer,int x,int y,int w,int h)
{
    SDL_Rect a = {x,y,w,h};
    SDL_RenderFillRect(labyrenderer->renderer, &a);
}

void renderFloor(Labyrendu* labyrenderer)
{
    SDL_Rect a = {0.0,0.0,max,max};
    SDL_Rect b = {0.0,SCREEN_HEIGHT/2,SCREEN_WIDTH,SCREEN_HEIGHT/2};

    SDL_RenderCopy(labyrenderer->renderer,labyrenderer->textureFloor,&a,&b);
}

void renderSky(Labyrendu* labyrenderer)
{
    SDL_Rect a = {0.0,0.0,max,max};
    SDL_Rect b = {0.0,0.0,SCREEN_WIDTH,SCREEN_HEIGHT/2};

    SDL_RenderCopy(labyrenderer->renderer,labyrenderer->textureSky,&a,&b);
}

void renderAll(Labyrendu* labyrender)
{
    renderFloor(labyrender);
    renderSky(labyrender);
}

void renderWall(Labyrendu* labyrenderer,GameMap* map, Player* p)
{
    SDL_SetRenderTarget(labyrenderer->renderer,labyrenderer->textureWall);
    for(size_t i=0;i<SCREEN_WIDTH;i++){
        float angle = p->angle - (pi/3)/2 + (pi/3) * i / (float)SCREEN_WIDTH;
        for(float j=0;j<20;j+=0.05){
            float x=p->x + j * cos(angle);
            float y=p->y + j * sin(angle);
            if(map->map[(int)y][(int)x] == 1){
                size_t hauteur = SCREEN_HEIGHT / j*(cos(angle-p->angle));
                SDL_RenderDrawLine(labyrenderer->renderer,i,SCREEN_HEIGHT/2-hauteur,i,SCREEN_HEIGHT/2+hauteur/2);
            }
        }
    }
}


void cleanSDL(SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_DestroyRenderer(renderer);  
    SDL_DestroyWindow(window);
    SDL_Quit();
}


