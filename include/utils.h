#ifndef UTILS_H
#define UTILS_H

#include <SDL.h>
#include <SDL_ttf.h>

// Fonctions utilitaires
int random_range(int min, int max);
void render_text(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y, SDL_Color color);

#endif // UTILS_H
