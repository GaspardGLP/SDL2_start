#ifndef MENU_H
#define MENU_H

#include <SDL.h>
#include <SDL_ttf.h>
#include "game_logic.h"

// Fonctions pour gérer les menus
void show_main_menu(SDL_Renderer* renderer, TTF_Font* font, GameState* game_state);
void show_game_over(SDL_Renderer* renderer, TTF_Font* font, GameState* game_state);

#endif // MENU_H
