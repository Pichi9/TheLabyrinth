#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Map/map.h"
#include "Player/player.h"
#include "Render/render.h"



int main(int argc, char const *argv[]) 
{
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    initSDL(&window, &renderer);
    Labyrendu* labyrenderer = createrender();
    initTextures(labyrenderer);
    GameMap* map = CreateMap("Map/map.txt");
    Player* p = malloc(sizeof(Player));
    initPlayer(p);
    int win = 0;
    while(win==0)
    {
        renderAll(labyrenderer);
        renderWall(labyrenderer,map,p);
        SDL_RenderPresent(labyrenderer->renderer);
    }
    SDL_Quit();
    return 0;
}