#ifndef EVENTS_H
#define EVENTS_H

#include <SDL.h>
#include "game_logic.h"

// Gestion des événements dans le menu principal
void handle_menu_events(SDL_Event* event, enum GameState* game_state);

// Gestion des événements dans le jeu
void handle_game_events(SDL_Event* event, int* running);

// Gestion des événements dans l'écran de game over
void handle_game_over_events(SDL_Event* event, enum GameState* game_state);

#endif // EVENTS_H
