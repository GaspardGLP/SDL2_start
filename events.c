#include "include/events.h"

void handle_menu_events(SDL_Event* event, enum GameState* game_state) {
    if (event->type == SDL_KEYDOWN) {
        switch (event->key.keysym.sym) {
        case SDLK_RETURN: // Touche Entrée pour commencer le jeu
            *game_state = GAME;
            break;
        case SDLK_q: // Touche Q pour quitter
            *game_state = QUIT;
            break;
        default:
            break;
        }
    }
}

void handle_game_events(SDL_Event* event, int* running) {
    if (event->type == SDL_KEYDOWN) {
        switch (event->key.keysym.sym) {
        case SDLK_ESCAPE: // Touche Échap pour quitter le jeu
            *running = 0;
            break;
        default:
            break;
        }
    }
}

void handle_game_over_events(SDL_Event* event, enum GameState* game_state) {
    if (event->type == SDL_KEYDOWN) {
        switch (event->key.keysym.sym) {
        case SDLK_RETURN: // Touche Entrée pour retourner au menu principal
            *game_state = MENU;
            break;
        case SDLK_q: // Touche Q pour quitter
            *game_state = QUIT;
            break;
        default:
            break;
        }
    }
}
