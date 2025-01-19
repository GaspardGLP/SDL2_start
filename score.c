#include "include/init.h"
#include "include/events.h"
#include "include/game_logic.h"
#include "include/render.h"
#include "include/menu.h"
#include "include/score.h"
#include "include/utils.h"

// Fonction pour initialiser le score
void initialize_score(Score* score) {
    score->current_score = 0;
    score->high_score = 0;
}

// Ajouter des points au score actuel
void add_points(Score* score, int points) {
    score->current_score += points;
    if (score->current_score > score->high_score) {
        score->high_score = score->current_score;
    }
}

// Rendre le score à l'écran
void render_score(SDL_Renderer* renderer, TTF_Font* font, Score* score, int x, int y) {
    char score_text[50];
    snprintf(score_text, sizeof(score_text), "Score: %d", score->current_score);

    SDL_Color white = {255, 255, 255, 255};
    SDL_Surface* surface = TTF_RenderText_Solid(font, score_text, white);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect text_rect = {x, y, surface->w, surface->h};

    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, &text_rect);
    SDL_DestroyTexture(texture);
}

// Charger le meilleur score depuis un fichier
void load_high_score(Score* score, const char* file_path) {
    FILE* file = fopen(file_path, "r");
    if (file) {
        fscanf(file, "%d", &score->high_score);
        fclose(file);
    } else {
        // Si le fichier n'existe pas, initialiser à 0
        score->high_score = 0;
    }
}

// Sauvegarder le meilleur score dans un fichier
void save_high_score(Score* score, const char* file_path) {
    FILE* file = fopen(file_path, "w");
    if (file) {
        fprintf(file, "%d", score->high_score);
        fclose(file);
    }
}
