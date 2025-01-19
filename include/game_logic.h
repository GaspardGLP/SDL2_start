#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <SDL.h>
#include <SDL_ttf.h>

// Définition des états du jeu
typedef enum {
    MENU,
    GAME,
    GAME_OVER,
    QUIT
} GameState;

// Fonctions liées à la logique du jeu
void update_logo_position(SDL_Rect* logo, float* speed_x, float* speed_y, int window_width, int window_height, Uint8* r, Uint8* g, Uint8* b, float deltaTime);

// Déclaration de la fonction principale pour jouer
void play_game(GameState* game_state, SDL_Renderer* renderer, TTF_Font* font);

#endif // GAME_LOGIC_H
