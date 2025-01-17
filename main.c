#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include "include/init.h"
#include "include/events.h"
#include "include/render.h"
#include "include/game_logic.h"
#include "include/menu.h"

enum GameState {
    MENU,
    GAME,
    GAME_OVER,
    QUIT
};

int main(int argc, char* argv[]) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    int running = 1;
    enum GameState game_state = MENU;

    // Initialisation de SDL
    if (!initialize(&window, &renderer, 800, 600)) {
        return -1;
    }

    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }

            // Gestion des événements selon l'état du jeu
            switch (game_state) {
            case MENU:
                handle_menu_events(&event, &game_state);
                break;
            case GAME:
                handle_game_events(&event, &running);
                break;
            case GAME_OVER:
                handle_game_over_events(&event, &game_state);
                break;
            }
        }

        // Mise à jour et rendu selon l'état
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Nettoyage de l'écran
        SDL_RenderClear(renderer);

        switch (game_state) {
        case MENU:
            show_main_menu(renderer);
            break;
        case GAME:
            update_game_logic();
            render_game(renderer);
            break;
        case GAME_OVER:
            show_game_over(renderer);
            break;
        }

        SDL_RenderPresent(renderer); // Afficher le rendu final
        SDL_Delay(16); // Limitation de la vitesse à ~60 FPS
    }

    // Nettoyage des ressources
    clean_SDL(window, renderer);
    return 0;
}
