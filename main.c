#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Map/map.h"
#include "Player/player.h"
#include "Render/render.h"

void handle_events(SDL_Event *event, Player *p, Map *m, SDL_Window *window){
    Uint8 *keystates;
    while(SDL_PollEvent(event)){
        if(event->type == SDL_QUIT){
            SDL_QUIT();
        }
        if(event->key.keysym.sym==SDLK_z){
            if(isWall(m,p->x + p->dirX*Speed, p->y + p->dirY*Speed))
            { break };
        }
        if(event->key.keysym.sym==SDLK_q){
            if(isWall(m,p->x - p->dirX*Speed,p->y - p->dirY*Speed))
            { break };
        }
        if(event->key.keysym.sym==SDLK_s){
            if(isWall(m,p->x - p->dirX*Speed,p->y - p->dirY*Speed))
        }
        if(event->key.keysym.sym==SDLK_d){
            if(isWall(m,p->x + p->dirX*Speed, p->y + p->dirY*Speed))
            { break };
        }
    }
}

int main(int argc, char const *argv[]) 
{
    printf("Hello, World!\n");
    return 0;
}
