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

