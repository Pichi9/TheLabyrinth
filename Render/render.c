#include "render.h"

void initSDL()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("Erreur dans l'initialisation de SDL : %s\n", SDL_GetError()); // Gestion des erreurs
        return;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) 
    {
        printf("Erreur dans l'initialisation de SDL: %s\n", Mix_GetError()); // Gestion des erreurs
    }

    if (TTF_Init() < 0) 
    {
        printf("Erreur dans l'initialisation de TTF: %s\n", Mix_GetError()); // Gestion des erreurs
    }
    

}

Labyrendu* createrender()
{
    Labyrendu* labyrenderer = calloc(1, sizeof(Labyrendu)); // Allocation de la mémoire pour le rendu
    if (labyrenderer == NULL) 
    {
        printf("Erreur dans l'allocation pour le rendu\n"); // Gestion des erreurs
        return NULL;   
    }

    labyrenderer->window = SDL_CreateWindow("Le Labyrinthe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL); // Créer la fenetre a partir des constantes
    if (labyrenderer->window == NULL) 
    {
        printf("Erreur dans la création de la fenêtre : %s\n", SDL_GetError()); // Gestions des erreurs
        free(labyrenderer);
        return NULL;
    }

    labyrenderer->renderer = SDL_CreateRenderer(labyrenderer->window, -1, SDL_RENDERER_SOFTWARE); // Créer le rendu pour la fenetre
    if (labyrenderer->renderer == NULL) 
    {
        printf("Erreur de création du rendu : %s\n", SDL_GetError()); // Gestion des erreurs
        SDL_DestroyWindow(labyrenderer->window); // Déstruction de la fenetre en cas d'echec
        free(labyrenderer); // On libère la mémoire
        return NULL;
    }
    return labyrenderer; // On retourne le rendu 
}


void initTextures(Labyrendu* labyrenderer)
{
    SDL_Surface* tempSurface; // Notre variable temporaire qui stock la surface 
    tempSurface = SDL_LoadBMP("Ressources/Textures/Floor.bmp");
    labyrenderer->textureFloor = SDL_CreateTextureFromSurface(labyrenderer->renderer, tempSurface); // Créer une texture à partir de la surface
    SDL_FreeSurface(tempSurface); // On libére la mémoire pour la variable temporaire, pour la réutiliser

    tempSurface = SDL_LoadBMP("Ressources/Textures/Sky.bmp");
    labyrenderer->textureSky = SDL_CreateTextureFromSurface(labyrenderer->renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    // Tentative d'application de textures pour les murs, mais finalement non implémentée
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
    SDL_SetRenderDrawColor(labyrenderer->renderer,80,90,95,0x80);
    for(size_t i=0;i<SCREEN_WIDTH;i++)
    {
        float angle = p->angle - (pi/3)/2 + (pi/3) * i / (float)SCREEN_WIDTH;
        for(float j=0;j<20;j+=0.05)
        {
            float x=p->x + j * cos(angle);
            float y=p->y + j * sin(angle);
            if(map->map[(int)y][(int)x] == 1)
            {
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


