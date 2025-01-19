#include <stdio.h>
#include <SDL.h>
#include "include/init.h"
#include "include/events.h"
#include "include/game_logic.h"
#include "include/render.h"
#include "include/menu.h"
#include "include/score.h"
#include "include/utils.h"

void update_logo_position(SDL_Rect* logo, float* speed_x, float* speed_y, int window_width, int window_height, Uint8* r, Uint8* g, Uint8* b, float deltaTime) {
    logo->x += (int)(*speed_x * deltaTime);
    logo->y += (int)(*speed_y * deltaTime);

    if (logo->x <= 0 || logo->x + logo->w >= window_width) {
        *speed_x = -*speed_x;
        *r = random_range(0, 255);
        *g = random_range(0, 255);
        *b = random_range(0, 255);
    }

    if (logo->y <= 0 || logo->y + logo->h >= window_height) {
        *speed_y = -*speed_y;
        *r = random_range(0, 255);
        *g = random_range(0, 255);
        *b = random_range(0, 255);
    }
}

void play_game(GameState* game_state, SDL_Renderer* renderer, TTF_Font* font) {
    int running = 1;

    // Initialisation d'un exemple d'objet (balle ou autre)
    SDL_Rect ball = {400, 300, 20, 20};
    float speed_x = 200.0f;
    float speed_y = 200.0f;

    Uint8 r = 255, g = 255, b = 255;
    Uint32 lastTime = SDL_GetTicks();

    while (running && *game_state == GAME) {
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        // Gestion des événements
        events_handling(&running, game_state);

        // Mise à jour de la position de la balle
        update_logo_position(&ball, &speed_x, &speed_y, 800, 600, &r, &g, &b, deltaTime);

        // Rendu
        render_logo(renderer, &ball, r, g, b);

        SDL_Delay(16); // Limite à ~60 FPS
    }

    if (*game_state != QUIT) {
        *game_state = GAME_OVER;
    }
}
