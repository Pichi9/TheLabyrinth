#include "tscreen.h"



int getTimeLeft(int beginTime, int endTime)
{
    return Temps - (endTime - beginTime);
}

void createScore(const char *filename,const char* nom, int beginTime, int endTime)
{
    int score = getTimeLeft(beginTime,endTime);
    FILE *file = fopen(filename, "a");
    fprintf(file,"\n%s : %d seconds left.",nom,score);
    fclose(file);  
}

void applyText(SDL_Renderer *renderer, int x, int y, int w, int h, const char* text, TTF_Font *font)
{
    SDL_Color color = {255,255,0};
    SDL_Surface *surface = TTF_RenderText_Solid(font,text,color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect rect = {x,y,w,h};
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void freeFont(TTF_Font* font)
{
    TTF_CloseFont(font);
}

void endImageLoose(SDL_Renderer *renderer, const char *image) 
{
    SDL_Surface* endImage = SDL_LoadBMP(image); // Chargement de l'image
    SDL_Texture* endImageTexture = SDL_CreateTextureFromSurface(renderer, endImage); // On crée la texture à partir de la surface
    SDL_FreeSurface(endImage); // On libère la surface
    SDL_RenderClear(renderer); // Nettoyage du rendu
    SDL_RenderCopy(renderer, endImageTexture, NULL, NULL);
    SDL_RenderPresent(renderer);
    SDL_Delay(10000); // L'image apparait 10 secondes 
    SDL_DestroyTexture(endImageTexture); // On détruit la texture
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





