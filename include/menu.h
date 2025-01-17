#ifndef MENU_H
#define MENU_H

#include <SDL.h>
#include <SDL_ttf.h>

// Initialiser le menu
int initialize_menu(SDL_Renderer* renderer, TTF_Font** font);

// Afficher le menu principal
void render_main_menu(SDL_Renderer* renderer, TTF_Font* font, int selected_option);

// Afficher l'écran de fin de partie
void render_game_over_menu(SDL_Renderer* renderer, TTF_Font* font, int score);

// Nettoyer les ressources liées au menu
void clean_menu(TTF_Font* font);

#endif // MENU_H
