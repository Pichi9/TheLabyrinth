#ifndef CONSTANTES_H
#define CONSTANTES_H


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>

// Taille de l'écran
#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 600

// Taille de la map
#define MAP_HEIGHT 15
#define MAP_WIDTH 15

// Taille d'un mur
#define WALL_WIDTH 50
#define WALL_HEIGHT 200

// Taille du sol
#define FLOOR_WIDTH 800
#define FLOOR_HEIGHT 300

// Valeurs mathématiques
#define pi M_PI
#define max INT_MAX

// Vitesse du joueur
#define Speed 0.1

// Temps de jeu
#define Temps 180


// Zoom porte de fin
#define SCALE_BEGIN 1.0f    // Échelle de début de zoom
#define SCALE_END 20.0f      // Échelle de fin de zoom
#define ZOOM_IMAGE 20          // Nombre d'images dans le zoom
#define ZOOM_FRAME 60     // 60 IMS 


// Temps entre les pas
#define TIME_STEP 1000
#endif