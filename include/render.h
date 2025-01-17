#ifndef RENDER_H
#define RENDER_H

#include <SDL.h>
#include "game_logic.h"

// Rendre la raquette
void render_paddle(SDL_Renderer* renderer, Paddle* paddle);

// Rendre la balle
void render_ball(SDL_Renderer* renderer, Ball* ball);

// Rendre les briques
void render_bricks(SDL_Renderer* renderer, Brick bricks[], int brick_count);

// Rendre l'écran de jeu
void render_game(SDL_Renderer* renderer, Paddle* paddle, Ball* ball, Brick bricks[], int brick_count);

#endif // RENDER_H
