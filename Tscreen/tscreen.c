#include "tscreen.h"


void pause(int time){
    SDL_Delay(time*0.001);
}

void createScore(const char *filename,char* nom, int beginTime, int endTime){
    int score = (Temps + (beginTime - endTime)) * 10;
    FILE *file = fopen(filename, "w");
    fprintf(file,"%s : %d",nom,time);
    fclose(file);
}


void endImageLoose(SDL_Renderer *renderer, const char *image) 
{
    SDL_Surface* endImage = SDL_LoadBMP(image);
    SDL_Texture* endImageTexture = SDL_CreateTextureFromSurface(renderer, endImage);
    SDL_FreeSurface(endImage); 
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, endImageTexture, NULL, NULL);
    SDL_RenderPresent(renderer);
    SDL_Delay(10000); 
    SDL_DestroyTexture(endImageTexture);
}

void startImage(SDL_Renderer *renderer, const char *image)
{
    SDL_Surface* startImage = SDL_LoadBMP(image);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, startImage);
    SDL_FreeSurface(startImage); 
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
    SDL_Delay(10000); 
    SDL_DestroyTexture(texture);
}


void endImageWin(SDL_Renderer *renderer, const char *image, int zoom) 
{
    SDL_Surface *surface = SDL_LoadBMP(image); // On charge notre image 
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface); // On crée la texture à partir de la surface
    SDL_FreeSurface(surface); // On libère la surface
    int width, height; 
    SDL_GetRendererOutputSize(renderer, &width, &height); // Récupérer la taille de la fenêtre
    SDL_Rect destRect = {0, 0, width, height}; // Destination rect centrée à l'écran
    if (zoom) 
    {
        // Ici on calcule la difference de taille entre le début et la fin du zoom
        float scaleIncrement = (SCALE_END - SCALE_BEGIN) / ZOOM_IMAGE;
        float currentScale = SCALE_BEGIN;
        // Notre boucle effectuant le zoom
        for (int i = 0; i < ZOOM_IMAGE; ++i) 
        {
            currentScale = currentScale + scaleIncrement; // Augmente l'echelle
            destRect.w = (int)(width * currentScale); // On ajuste la taille du rectangle (largeur)
            destRect.h = (int)(height * currentScale); // On ajuste la taille du rectangle (hauteur)
            destRect.x = (width - destRect.w) / 2; // On dirige le zoom vers la porte de sortie (largeur)
            destRect.y = (height - destRect.h) / 1.5; // On dirige le zoom vers la porte de sortie (hauteur)

            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, texture, NULL, &destRect);
            SDL_RenderPresent(renderer);
            SDL_Delay(ZOOM_FRAME);
        }
    } 
    else 
    {
        SDL_RenderCopy(renderer, texture, NULL, &destRect);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(texture);
}

