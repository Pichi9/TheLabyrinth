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
    initSDL();
	Labyrendu* labyrenderer = createrender();
	initTextures(labyrenderer);
	GameMap* map = CreateMap("Map/map.txt");
	Player* p = malloc(sizeof(Player));
	initPlayer(p);
	int victoire = 0;
	while(victoire==0){
		renderAll(labyrenderer);
		renderWall(labyrenderer,map,p);
		SDL_RenderPresent(labyrenderer->renderer);

	}
	SDL_Quit();
    return 0;
}
