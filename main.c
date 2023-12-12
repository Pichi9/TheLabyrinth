#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Map/map.h"
#include "Player/player.h"
#include "Render/render.h"
#include "Tscreen/tscreen.h"

// Notre fonction qui libère les ressources utilisées dans le jeu 
void freeAll(Player *p, GameMap *map, SDL_Window *window, Labyrendu *labyrenderer)
{
    freeMap(map); // Libération de la mémoire allouée pour la carte
    freePlayer(p); // Libération de la mémoire allouée pour le joueur
    cleanSDL(window,labyrenderer->renderer); // Nettoyage des ressources SDL
}

// void finDeJeu(int beginTime, int endTime){}

// Notre fonction qui gère les évènements du jeu (touches du claviers, souris)
int handle_events(SDL_Event *event, Player *p, GameMap *map, SDL_Window *window,Labyrendu *labyrenderer)
{
    Uint8 *keystates;
    while(SDL_PollEvent(event))
    {
        if(event->key.keysym.sym==SDLK_ESCAPE)
        {	
            return 1;
        }

        // Si la touche Z est pressée
        if(event->key.keysym.sym==SDLK_z)
        {  
            if(!isWall(map,p->x + p->dirX*Speed, p->y + p->dirY*Speed)) // Verifie si il y'a un mur qui rends le déplacement impossible
            {
                p->x += p->dirX*Speed; // Met à jour la position (x) du joueur en fonction de la direction et la vitesse 
                p->y += p->dirY*Speed; // Met à jour la position (y) du joueur en fonction de la direction et la vitesse
                anglePlayer(p); // Ajuste l'angle du joueur
            };
        }
        // Si la touche Q est pressée
        else if(event->key.keysym.sym==SDLK_q)
        {
            if(!isWall(map,p->x - p->dirX*Speed,p->y - p->dirY*Speed)) // Verifie si il y'a un mur qui rends le déplacement impossible
            {
                p->angle += pi/2; // Modifie l'angle du joueur
                anglePlayer(p); // Ajuste l'angle du joueur
                p->x-=p->dirX*Speed; // Met à jour la position (x) du joueur en fonction de la direction et la vitesse
                p->y-=p->dirY*Speed; // Met à jour la position (y) du joueur en fonction de la direction et la vitesse
                p->angle -= pi/2; // Modifie l'angle du joueur
                anglePlayer(p); // Ajuste l'angle du joueur
            };
        }
        // Si la touche S est pressée
        else if(event->key.keysym.sym==SDLK_s)
        {
            if(!isWall(map,p->x - p->dirX*Speed,p->y - p->dirY*Speed)) // Verifie si il y'a un mur qui rends le déplacement impossible
            {
                p->x -= p->dirX*Speed; // Met à jour la position (x) du joueur en fonction de la direction et la vitesse
                p->y -= p->dirY*Speed; // Met à jour la position (y) du joueur en fonction de la direction et la vitesse
                anglePlayer(p); // Ajuste l'angle du joueur
            }
        }
        // Si la touche D est pressée
        else if(event->key.keysym.sym==SDLK_d)
        {
            if(!isWall(map,p->x + p->dirX*Speed, p->y + p->dirY*Speed)) // Verifie si il y'a un mur qui rends le déplacement impossible
            {
                p->angle += pi/2; // Modifie l'angle du joueur
                anglePlayer(p); // Ajuste l'angle du joueur
                p->x+=p->dirX*Speed; // Met à jour la position (x) du joueur en fonction de la direction et la vitesse
                p->y+=p->dirY*Speed; // Met à jour la position (y) du joueur en fonction de la direction et la vitesse
                p->angle -= pi/2; // Modifie l'angle du joueur
                anglePlayer(p); // Ajuste l'angle du joueur
            };
        }
        // Traitement des mouvements de la souris
        if(event->type==SDL_MOUSEMOTION)
        {
            float move;
            // Détermine la direction du mouvement de la sourie
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
            anglePlayer(p); // Ajuste l'angle du joueur
            SDL_WarpMouseInWindow(window,SCREEN_WIDTH/2,SCREEN_HEIGHT/2); // Remet la souris au centre
        }
    }
    return 0;
}

int main(int argc, char const *argv[]) 
{
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    initSDL(&window, &renderer);
    Labyrendu* labyrenderer = createrender();
    initTextures(labyrenderer);
    GameMap* map = malloc(2*sizeof(GameMap));
    map = CreateMap("Map/map.txt");
    Player* p = malloc(sizeof(Player));
    initPlayer(p);
    SDL_Event* event = malloc(sizeof(SDL_Event));
    SDL_ShowCursor(SDL_DISABLE);
    int win = 0;
    while(win==0)
    {
        renderAll(labyrenderer);
        win = handle_events(event,p,map,window,labyrenderer);
        renderWall(labyrenderer,map,p);
        SDL_RenderPresent(labyrenderer->renderer);
        if(end(map,p->x,p->y))
        {
            win=1;
            printf("Vous avez trouver la sortie !\n");
        }
    }
    pause(5);
    //finDeJeu()
    freeAll(p,map,window,labyrenderer);
    printf("Fin de la partie !\n");
    return 0;
}