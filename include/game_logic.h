#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <SDL.h>

// Structure pour la raquette
typedef struct {
    SDL_Rect rect;  // Position et taille
    int speed;      // Vitesse de déplacement
} Paddle;

// Structure pour la balle
typedef struct {
    SDL_Rect rect;  // Position et taille
    int speed_x;    // Vitesse en X
    int speed_y;    // Vitesse en Y
} Ball;

// Structure pour une brique
typedef struct {
    SDL_Rect rect;  // Position et taille
    int is_destroyed; // 0 si intacte, 1 si détruite
} Brick;

// Initialiser les éléments du jeu
void initialize_game(Paddle* paddle, Ball* ball, Brick bricks[], int* brick_count, int screen_width, int screen_height);

// Mettre à jour la logique du jeu
void update_game_logic(Paddle* paddle, Ball* ball, Brick bricks[], int brick_count, int screen_width, int screen_height, int* game_over);

#endif // GAME_LOGIC_H
