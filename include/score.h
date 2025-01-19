#ifndef SCORE_H
#define SCORE_H

#include <SDL.h>
#include <SDL_ttf.h>

// Structure représentant le score
typedef struct Score {
    int current_score;     // Score actuel
    int high_score;        // Meilleur score
} Score;

// Initialiser le score
void initialize_score(Score* score);

// Ajouter des points au score actuel
void add_points(Score* score, int points);

// Rendre le score à l'écran
void render_score(SDL_Renderer* renderer, TTF_Font* font, Score* score, int x, int y);

// Charger le meilleur score depuis un fichier
void load_high_score(Score* score, const char* file_path);

// Sauvegarder le meilleur score dans un fichier
void save_high_score(Score* score, const char* file_path);

#endif // SCORE_H
