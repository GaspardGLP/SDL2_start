#include "include/init.h"
#include "include/events.h"
#include "include/game_logic.h"
#include "include/render.h"
#include "include/menu.h"
#include "include/score.h"
#include "include/utils.h"
#include <SDL.h>

void events_handling(int* running, GameState* game_state) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            *game_state = QUIT;
            *running = 0;
        }
    }
}
