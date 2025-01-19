#include "include/init.h"
#include "include/events.h"
#include "include/game_logic.h"
#include "include/render.h"
#include "include/menu.h"
#include "include/score.h"
#include "include/utils.h"
#include <SDL.h>

void render_logo(SDL_Renderer* renderer, SDL_Rect* logo, Uint8 r, Uint8 g, Uint8 b) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderFillRect(renderer, logo);
    SDL_RenderPresent(renderer);
}
