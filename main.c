#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Map/map.h"
#include "Player/player.h"
#include "Render/render.h"


void freeAll(Player *p, GameMap *map, SDL_Window *window, Labyrendu *labyrenderer){
    freeMap(map);
    freePlayer(p);
    cleanSDL(window,labyrenderer);
}


void handle_events(SDL_Event *event, Player *p, GameMap *map, SDL_Window *window){
    Uint8 *keystates;
    while(SDL_PollEvent(event)){
        if(event->type == SDL_QUIT){
            SDL_Quit();
        }
        if(event->key.keysym.sym==SDLK_z){
            if(!isWall(map,p->x + p->dirX*Speed, p->y + p->dirY*Speed)){
                p->x += p->dirX*Speed;
                p->y += p->dirY*Speed;
                anglePlayer(p);
            };
        }
        else if(event->key.keysym.sym==SDLK_q){
            if(!isWall(map,p->x - p->dirX*Speed,p->y - p->dirY*Speed))
            {
                p->angle += pi/2;
                anglePlayer(p);
                p->x-=p->dirX*Speed;
                p->y-=p->dirY*Speed;
                p->angle -= pi/2;
                anglePlayer(p); //réajuster l'angle à chaque modif de celui ci
            };
        }
        else if(event->key.keysym.sym==SDLK_s){
            if(!isWall(map,p->x - p->dirX*Speed,p->y - p->dirY*Speed))
            {
                p->x -= p->dirX*Speed;
                p->y -= p->dirY*Speed;
                anglePlayer(p);
            }
        }
        else if(event->key.keysym.sym==SDLK_d){
            if(!isWall(map,p->x + p->dirX*Speed, p->y + p->dirY*Speed))
            {
                p->angle += pi/2;
                anglePlayer(p);
                p->x+=p->dirX*Speed;
                p->y+=p->dirY*Speed;
                p->angle -= pi/2;
                anglePlayer(p); //réajuster l'angle à chaque modif de celui ci
            };
        }
        if(event->type==SDL_MOUSEMOTION)
        {
            float move;
            if(event->motion.x>SCREEN_WIDTH/2)
            {
                move = 0.01;
            } 
            else if(event->motion.x < SCREEN_WIDTH/2) 
            {
                move = -0.01;
            }
             else 
            {
                move = 0;
            }
            p->angle += move;
            anglePlayer(p);
            SDL_WarpMouseInWindow(window,SCREEN_WIDTH/2,SCREEN_HEIGHT/2);
        }
    }
}

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
    freeAll(map,p,window,labyrenderer);
    return 0;
}