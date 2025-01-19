#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include "include/init.h"
#include "include/events.h"
#include "include/game_logic.h"
#include "include/render.h"
#include "include/menu.h"
#include "include/score.h"
#include "include/utils.h"

void draw_bricks(SDL_Renderer* renderer, Brick* bricks, int brick_count) {
    for (int i = 0; i < brick_count; ++i) {
        SDL_SetRenderDrawColor(renderer, bricks[i].color.r, bricks[i].color.g, bricks[i].color.b, 255);
        SDL_RenderFillRect(renderer, &bricks[i].rect);
    }
}

void draw_paddle(SDL_Renderer* renderer, Paddle* paddle) {
    SDL_SetRenderDrawColor(renderer, paddle->color.r, paddle->color.g, paddle->color.b, 255);
    SDL_RenderFillRect(renderer, &paddle->rect);
}

void draw_ball(SDL_Renderer* renderer, Ball* ball) {
    SDL_SetRenderDrawColor(renderer, ball->color.r, ball->color.g, ball->color.b, 255);
    SDL_RenderFillRect(renderer, &ball->rect);
}

void play_game(GameState* game_state, SDL_Renderer* renderer) {
    int running = 1;

    // Briques
    const int brick_row_count = 5;
    const int brick_column_count = 8;
    const int brick_width = 80;
    const int brick_height = 20;
    Brick bricks[brick_row_count * brick_column_count];

    for (int i = 0; i < brick_row_count; ++i) {
        for (int j = 0; j < brick_column_count; ++j) {
            bricks[i * brick_column_count + j] = (Brick){
                .rect = { j * brick_width + 100, i * brick_height + 50, brick_width, brick_height },
                .color = { (i * 50) % 255, (j * 100) % 255, (i * j * 50) % 255 }
            };
        }
    }

    // Barre
    Paddle paddle = { .rect = { 350, 550, 100, 20 }, .color = {255, 255, 255} };

    // Balle
    Ball ball = { .rect = { 400, 300, 20, 20 }, .speed_x = 150.0f, .speed_y = -150.0f, .color = {255, 0, 0} };

    SDL_Event event;
    Uint32 lastTime = SDL_GetTicks();

    while (running && *game_state == GAME) {
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        events_handling(&running, game_state, &event, &paddle);

        // Mise à jour de la position de la balle
        ball.rect.x += (int)(ball.speed_x * deltaTime);
        ball.rect.y += (int)(ball.speed_y * deltaTime);

        // Gestion des collisions avec les murs
        if (ball.rect.x <= 0 || ball.rect.x + ball.rect.w >= 800) {
            ball.speed_x = -ball.speed_x;
        }
        if (ball.rect.y <= 0) {
            ball.speed_y = -ball.speed_y;
        }

        if (ball.rect.y + ball.rect.h >= 600) {
            *game_state = GAME_OVER;  // Le joueur perd si la balle touche le bas
        }

        // Dessiner les briques
        draw_bricks(renderer, bricks, brick_row_count * brick_column_count);
        draw_paddle(renderer, &paddle);
        draw_ball(renderer, &ball);

        SDL_RenderPresent(renderer);
        SDL_Delay(16); // Limite à ~60 FPS
    }
}

int main(int argc, char* argv[]) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    if (!initialize(&window, &renderer, 800, 600)) {
        return -1;
    }

    GameState game_state = MENU;
    int running = 1;

    while (running) {
        switch (game_state) {
        case MENU:
            show_main_menu(renderer, NULL, &game_state);
            break;
        case GAME:
            play_game(&game_state, renderer);
            break;
        case GAME_OVER:
            show_game_over(renderer, NULL, &game_state);
            break;
        case QUIT:
            running = 0;
            break;
        }
    }

    clean_SDL(window, renderer);
    return 0;
}
