#ifndef CONSTANTES_H
#define CONSTANTES_H


#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <time.h>

// Taille de l'écran
#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 600

// Taille de la map
#define MAP_HEIGHT 20
#define MAP_WIDTH 20

// Taille d'un mur
#define WALL_WIDTH 50
#define WALL_HEIGHT 200

// Valeurs mathématiques
#define pi M_PI
#define max INT_MAX

// Vitesse du joueur
#define Speed 0.1

// Temps de jeu
#define Temps 250

// Zoom porte de fin
#define SCALE_BEGIN 1.0f 
#define SCALE_END 10.0f      
#define ZOOM_IMAGE 20          
#define ZOOM_FRAME 60     


// Temps entre les pas
#define TIME_STEP 400

#endif