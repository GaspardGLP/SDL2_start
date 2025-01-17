#include "include/game_logic.h"
#include <stdio.h>

void initialize_game(Paddle* paddle, Ball* ball, Brick bricks[], int* brick_count, int screen_width, int screen_height) {
    // Initialiser la raquette
    paddle->rect.w = 100;
    paddle->rect.h = 20;
    paddle->rect.x = (screen_width - paddle->rect.w) / 2;
    paddle->rect.y = screen_height - 40;
    paddle->speed = 10;

    // Initialiser la balle
    ball->rect.w = 15;
    ball->rect.h = 15;
    ball->rect.x = (screen_width - ball->rect.w) / 2;
    ball->rect.y = screen_height / 2;
    ball->speed_x = 5;
    ball->speed_y = -5;

    // Initialiser les briques
    int rows = 5;
    int cols = 10;
    int brick_width = screen_width / cols;
    int brick_height = 20;
    *brick_count = rows * cols;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int index = i * cols + j;
            bricks[index].rect.w = brick_width - 2; // Marges entre les briques
            bricks[index].rect.h = brick_height - 2;
            bricks[index].rect.x = j * brick_width + 1;
            bricks[index].rect.y = i * brick_height + 1;
            bricks[index].is_destroyed = 0;
        }
    }
}

void update_game_logic(Paddle* paddle, Ball* ball, Brick bricks[], int brick_count, int screen_width, int screen_height, int* game_over) {
    // Déplacer la balle
    ball->rect.x += ball->speed_x;
    ball->rect.y += ball->speed_y;

    // Collision avec les murs
    if (ball->rect.x <= 0 || ball->rect.x + ball->rect.w >= screen_width) {
        ball->speed_x = -ball->speed_x;
    }
    if (ball->rect.y <= 0) {
        ball->speed_y = -ball->speed_y;
    }

    // Collision avec le bas (perte de la balle)
    if (ball->rect.y + ball->rect.h >= screen_height) {
        *game_over = 1; // Le jeu est terminé
    }

    // Collision avec la raquette
    if (SDL_HasIntersection(&ball->rect, &paddle->rect)) {
        ball->speed_y = -ball->speed_y;
    }

    // Collision avec les briques
    for (int i = 0; i < brick_count; i++) {
        if (!bricks[i].is_destroyed && SDL_HasIntersection(&ball->rect, &bricks[i].rect)) {
            ball->speed_y = -ball->speed_y;
            bricks[i].is_destroyed = 1; // Détruire la brique
        }
    }
}
