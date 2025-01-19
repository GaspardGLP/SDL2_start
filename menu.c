#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include "include/init.h"
#include "include/events.h"
#include "include/game_logic.h"
#include "include/render.h"
#include "include/menu.h"
#include "include/score.h"
#include "include/utils.h"

void show_main_menu(SDL_Renderer* renderer, TTF_Font* font, GameState* game_state) {
    SDL_Color white = {255, 255, 255, 255};
    render_text(renderer, font, "Main Menu - Press ENTER to Start", 100, 100, white);
    SDL_RenderPresent(renderer);

    SDL_Event event;
    while (SDL_WaitEvent(&event)) {
        if (event.type == SDL_QUIT) {
            *game_state = QUIT;
            return;
        }
        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN) {
            *game_state = GAME;
            return;
        }
    }
}

void show_game_over(SDL_Renderer* renderer, TTF_Font* font, GameState* game_state) {
    SDL_Color red = {255, 0, 0, 255};
    render_text(renderer, font, "Game Over - Press ESC to Exit", 100, 100, red);
    SDL_RenderPresent(renderer);

    SDL_Event event;
    while (SDL_WaitEvent(&event)) {
        if (event.type == SDL_QUIT) {
            *game_state = QUIT;
            return;
        }
        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
            *game_state = MENU;
            return;
        }
    }
}
