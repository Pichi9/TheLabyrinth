#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <time.h>
#include "Map/map.h"
#include "Player/player.h"
#include "Render/render.h"
#include "Tscreen/tscreen.h"



// Notre fonction qui libère les ressources utilisées dans le jeu 
void freeAll(Player *p, GameMap *map, SDL_Window *window, Labyrendu *labyrenderer, TTF_Font *font)
{
    freeMap(map); // Libération de la mémoire allouée pour la carte
    freePlayer(p); // Libération de la mémoire allouée pour le joueur
    freeFont(font); // Libération de la mémoire allouée pour la police d'écriture
    cleanSDL(window,labyrenderer->renderer); // Nettoyage des ressources SDL
}

// Notre fonction qui libère les ressources utilisées pour les sons
void freeMusic(Mix_Music *backgroundMusic, Mix_Chunk *stepSound, Mix_Chunk *winMusic, Mix_Chunk *looseMusic) 
{
    Mix_FreeMusic(backgroundMusic);
    Mix_FreeChunk(stepSound);
    Mix_FreeChunk(winMusic);
    Mix_FreeChunk(looseMusic);
}


Uint32 last = 0;
// Notre fonction qui gère les évènements du jeu (touches du claviers, souris)
int handle_events(SDL_Event *event, Player *p, GameMap *map, SDL_Window *window, Labyrendu *labyrenderer, Mix_Chunk *stepSound)
{
    Uint8 *keystates;
    Uint32 now = SDL_GetTicks(); // Cette fonction permet de récupérer le temps écoulé depuis l'appel de initSDL
    while(SDL_PollEvent(event))
    {
        // Si la touche Echap est pressée
        if(event->key.keysym.sym==SDLK_ESCAPE)
        {	
            return 1; // Ça quitte 
        }

        // Si la touche Z est pressée
        if(event->key.keysym.sym==SDLK_z)
        {  
            SDL_Scancode key = event->key.keysym.scancode;
            if(!isWall(map,p->x + p->dirX*Speed, p->y + p->dirY*Speed)) // Verifie si il y'a un mur qui rends le déplacement impossible
            {
                p->x += p->dirX*Speed; // Met à jour la position (x) du joueur en fonction de la direction et la vitesse 
                p->y += p->dirY*Speed; // Met à jour la position (y) du joueur en fonction de la direction et la vitesse
                anglePlayer(p); // Ajuste l'angle du joueur
                if (now - last > TIME_STEP) // Gestion du délai entre chaque son des pas (on vérifie que le temps entre le son soit d'au moins TIME_STEP)
                {
                    last = now;
                    Mix_PlayChannel(-1, stepSound, 0); // On joue le son du pas
                }
            };
        }
        // Si la touche Q est pressée
        else if(event->key.keysym.sym==SDLK_q)
        {
            SDL_Scancode key = event->key.keysym.scancode;
            if(!isWall(map,p->x + p->dirY*Speed, p->y - p->dirX*Speed)) // Changement ici
            {
                p->x += p->dirY*Speed; // Met à jour la position (x) du joueur en fonction de la direction et la vitesse
                p->y -= p->dirX*Speed; // Met à jour la position (y) du joueur en fonction de la direction et la vitesse
                anglePlayer(p); // Ajuste l'angle du joueur
                if (now - last > TIME_STEP) // Gestion du délai entre chaque son des pas (on vérifie que le temps entre le son soit d'au moins TIME_STEP)
                {
                    last = now;
                    Mix_PlayChannel(-1, stepSound, 0); // On joue le son du pas
                }
            };
        }
        // Si la touche S est pressée
        else if(event->key.keysym.sym==SDLK_s)
        {
            SDL_Scancode key = event->key.keysym.scancode;
            if(!isWall(map,p->x - p->dirX*Speed,p->y - p->dirY*Speed)) // Verifie si il y'a un mur qui rends le déplacement impossible
            {
                p->x -= p->dirX*Speed; // Met à jour la position (x) du joueur en fonction de la direction et la vitesse
                p->y -= p->dirY*Speed; // Met à jour la position (y) du joueur en fonction de la direction et la vitesse
                anglePlayer(p); // Ajuste l'angle du joueur
                if (now - last > TIME_STEP) // Gestion du délai entre chaque son des pas (on vérifie que le temps entre le son soit d'au moins TIME_STEP)
                {
                    last = now;
                    Mix_PlayChannel(-1, stepSound, 0); // On joue le son du pas
                }
            }
        }
        // Si la touche D est pressée
        else if(event->key.keysym.sym==SDLK_d)
        {
            if(!isWall(map,p->x - p->dirY*Speed,p->y + p->dirX*Speed)) // Changement ici
            {
                SDL_Scancode key = event->key.keysym.scancode;
                p->x -= p->dirY*Speed; // Met à jour la position (x) du joueur en fonction de la direction et la vitesse
                p->y += p->dirX*Speed; // Met à jour la position (y) du joueur en fonction de la direction et la vitesse
                anglePlayer(p); // Ajuste l'angle du joueur
                if (now - last > TIME_STEP) // Gestion du délai entre chaque son des pas (on vérifie que le temps entre le son soit d'au moins TIME_STEP)
                {
                    last = now;
                    Mix_PlayChannel(-1, stepSound, 0); // On joue le son du pas
                }
            };
        }

        // Traitement des mouvements de la souris
        if(event->type==SDL_MOUSEMOTION)
        {
            float move;
            // Détermine la direction du mouvement de la souris
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
    if(argc<2)
    {
        printf("Veuillez entrer votre nom en argument.\n");
        return 0;
    } 
    else 
    {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    Mix_Music *backgroundMusic = NULL;
    Mix_Chunk *stepSound = NULL;
    Mix_Chunk *winMusic = NULL;
    Mix_Chunk *looseMusic = NULL;
    initSDL();
    backgroundMusic = Mix_LoadMUS("Ressources/Sound/backgroundMusic.mp3");
    stepSound = Mix_LoadWAV("Ressources/Sound/pas.mp3");
    winMusic = Mix_LoadWAV("Ressources/Sound/winMusic.mp3");
    looseMusic = Mix_LoadWAV("Ressources/Sound/looseMusic.mp3");
    TTF_Font* font = TTF_OpenFont("Ressources/Font/police.ttf", 20);
    Labyrendu* labyrenderer = createrender();
    initTextures(labyrenderer);
    startImage(labyrenderer->renderer,"Ressources/Images/startimage.bmp");
    GameMap* map = malloc(2*sizeof(GameMap));
    map = CreateMap("Map/map.txt");
    Player* p = malloc(sizeof(Player));
    initPlayer(p,map);
    SDL_Event* event = malloc(sizeof(SDL_Event));
    SDL_ShowCursor(SDL_DISABLE);
    Mix_PlayMusic(backgroundMusic, -1);
    int beginTime = (int)time(NULL);
    int currentTime;
    char showTime[50];
    int win = 0;
        while(win==0)
        {
            renderAll(labyrenderer);
            win = handle_events(event, p, map, window, labyrenderer, stepSound);
            renderWall(labyrenderer,map,p);
            SDL_RenderPresent(labyrenderer->renderer);
            currentTime = (int)time(NULL);
            sprintf(showTime,"Time : %d",getTimeLeft(beginTime,currentTime));
            applyText(labyrenderer->renderer,0,SCREEN_HEIGHT/2,150,30,showTime,font);
            SDL_RenderPresent(labyrenderer->renderer);
            if(end(map,p->x,p->y))
            {
                win=1;
                printf("Vous avez trouvé la sortie !\n");
                int endTime = (int)time(NULL);
                createScore("Score.txt",argv[1], beginTime, endTime);
                Mix_HaltMusic(); // On coupe la musique du jeu
                Mix_PlayChannel(-1, winMusic, 0); // On active le son de la victoire
                endImageWin(labyrenderer->renderer, "Ressources/Images/endimagewin.bmp", 1); 
            } else if(currentTime-beginTime>=Temps)
            {
                win=1;
                printf("Vous n'avez pas trouvé la sortie !\n");
                Mix_HaltMusic(); // On coupe la musique du jeu
                Mix_PlayChannel(-1, looseMusic, 0); // On active le son de la défaite
                endImageLoose(labyrenderer->renderer, "Ressources/Images/endimageloose.bmp"); // Affiche l'image de défaite
            }
        }
        freeAll(p,map,window,labyrenderer,font); // On libère la mémoire
        freeMusic(backgroundMusic,stepSound,winMusic,looseMusic); 
        Mix_CloseAudio(); // On ferme l'audio
        printf("Fin de la partie !\n");
        return 0;
    }
}