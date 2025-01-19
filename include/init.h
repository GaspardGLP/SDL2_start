#ifndef INIT_H
#define INIT_H

#include <SDL.h>

// Initialisation de la fenêtre et du rendu
int initialize(SDL_Window** window, SDL_Renderer** renderer, int width, int height);

// Nettoyage des ressources SDL
void clean_SDL(SDL_Window* window, SDL_Renderer* renderer);

#endif // INIT_H
