#ifndef INIT_H
#define INIT_H

#include <SDL.h>

// Fonction pour initialiser SDL, la fenêtre et le renderer
int initialize(SDL_Window** window, SDL_Renderer** renderer, int width, int height);

// Fonction pour libérer les ressources SDL
void clean_SDL(SDL_Window* window, SDL_Renderer* renderer);

#endif // INIT_H
