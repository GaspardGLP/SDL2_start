#include "include/init.h"
#include <stdio.h>

// Fonction pour initialiser SDL, la fenêtre et le renderer
int initialize(SDL_Window** window, SDL_Renderer** renderer, int width, int height) {
    // Initialiser SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("Erreur : Impossible d'initialiser SDL : %s\n", SDL_GetError());
        return 0;
    }

    // Créer une fenêtre SDL
    *window = SDL_CreateWindow(
        "Casse-Brique",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_SHOWN
    );

    if (*window == NULL) {
        printf("Erreur : Impossible de créer la fenêtre : %s\n", SDL_GetError());
        SDL_Quit();
        return 0;
    }

    // Créer un renderer SDL
    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (*renderer == NULL) {
        printf("Erreur : Impossible de créer le renderer : %s\n", SDL_GetError());
        SDL_DestroyWindow(*window);
        SDL_Quit();
        return 0;
    }

    // Réussite
    return 1;
}

// Fonction pour libérer les ressources SDL
void clean_SDL(SDL_Window* window, SDL_Renderer* renderer) {
    if (renderer != NULL) {
        SDL_DestroyRenderer(renderer);
    }
    if (window != NULL) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}
