#include "include/render.h"

void render_paddle(SDL_Renderer* renderer, Paddle* paddle) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Blanc
    SDL_RenderFillRect(renderer, &paddle->rect);
}

void render_ball(SDL_Renderer* renderer, Ball* ball) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Rouge
    SDL_RenderFillRect(renderer, &ball->rect);
}

void render_bricks(SDL_Renderer* renderer, Brick bricks[], int brick_count) {
    for (int i = 0; i < brick_count; i++) {
        if (!bricks[i].is_destroyed) {
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Vert
            SDL_RenderFillRect(renderer, &bricks[i].rect);
        }
    }
}

void render_game(SDL_Renderer* renderer, Paddle* paddle, Ball* ball, Brick bricks[], int brick_count) {
    // Effacer l'écran avec une couleur noire
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Dessiner les éléments du jeu
    render_paddle(renderer, paddle);
    render_ball(renderer, ball);
    render_bricks(renderer, bricks, brick_count);

    // Mettre à jour l'écran
    SDL_RenderPresent(renderer);
}
