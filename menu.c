#include "include/menu.h"
#include <stdio.h>

// Fonction pour initialiser la police et vérifier les erreurs
int initialize_menu(SDL_Renderer* renderer, TTF_Font** font) {
    if (TTF_Init() == -1) {
        printf("Failed to initialize TTF: %s\n", TTF_GetError());
        return 0;
    }

    *font = TTF_OpenFont("assets/fonts/arial.ttf", 24);
    if (!*font) {
        printf("Failed to load font: %s\n", TTF_GetError());
        return 0;
    }

    return 1;
}

// Fonction pour afficher le menu principal
void render_main_menu(SDL_Renderer* renderer, TTF_Font* font, int selected_option) {
    const char* options[] = {"Start Game", "Exit"};
    int option_count = 2;

    SDL_Color white = {255, 255, 255, 255};
    SDL_Color yellow = {255, 255, 0, 255};

    // Effacer l'écran
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for (int i = 0; i < option_count; i++) {
        SDL_Color color = (i == selected_option) ? yellow : white;
        SDL_Surface* surface = TTF_RenderText_Solid(font, options[i], color);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

        SDL_Rect rect;
        rect.w = surface->w;
        rect.h = surface->h;
        rect.x = (800 - rect.w) / 2; // Centrer horizontalement
        rect.y = 200 + i * 50;      // Espacement vertical

        SDL_FreeSurface(surface);
        SDL_RenderCopy(renderer, texture, NULL, &rect);
        SDL_DestroyTexture(texture);
    }

    SDL_RenderPresent(renderer);
}

// Fonction pour afficher l'écran de fin de partie
void render_game_over_menu(SDL_Renderer* renderer, TTF_Font* font, int score) {
    char score_text[50];
    snprintf(score_text, sizeof(score_text), "Your Score: %d", score);

    SDL_Color white = {255, 255, 255, 255};

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_Surface* surface = TTF_RenderText_Solid(font, "Game Over", white);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect rect;
    rect.w = surface->w;
    rect.h = surface->h;
    rect.x = (800 - rect.w) / 2;
    rect.y = 150;

    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);

    surface = TTF_RenderText_Solid(font, score_text, white);
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    rect.w = surface->w;
    rect.h = surface->h;
    rect.x = (800 - rect.w) / 2;
    rect.y = 250;

    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);

    SDL_RenderPresent(renderer);
}

// Fonction pour nettoyer les ressources du menu
void clean_menu(TTF_Font* font) {
    if (font) {
        TTF_CloseFont(font);
    }
    TTF_Quit();
}
