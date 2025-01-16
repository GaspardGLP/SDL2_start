#define SDL_MAIN_HANDLED
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>

#define main SDL_main

int initialize(SDL_Window** window, SDL_Renderer** renderer, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not be initialized %s\n", SDL_GetError());
        return 0;
    }

    *window = SDL_CreateWindow("Casse-Brique", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (*window == NULL) {
        printf("ERROR: Failed to create the window %s\n", SDL_GetError());
        SDL_Quit();
        return 0;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (*renderer == NULL) {
        printf("ERROR: Failed to create the renderer %s\n", SDL_GetError());
        SDL_DestroyWindow(*window);
        SDL_Quit();
        return 0;
    }

    return 1;
}

void handle_events(int* running, SDL_Rect* paddle, int window_width) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            *running = 0;
        }
    }

    const Uint8* keystate = SDL_GetKeyboardState(NULL);
    if (keystate[SDL_SCANCODE_LEFT]) {
        paddle->x -= 10;
        if (paddle->x < 0) paddle->x = 0;
    }
    if (keystate[SDL_SCANCODE_RIGHT]) {
        paddle->x += 10;
        if (paddle->x + paddle->w > window_width) paddle->x = window_width - paddle->w;
    }
}

void update_ball(SDL_Rect* ball, float* ball_speed_x, float* ball_speed_y, SDL_Rect* paddle, int window_width, int window_height) {
    ball->x += (int)*ball_speed_x;
    ball->y += (int)*ball_speed_y;

    // Collision avec les murs
    if (ball->x <= 0 || ball->x + ball->w >= window_width) {
        *ball_speed_x = -*ball_speed_x;
    }
    if (ball->y <= 0) {
        *ball_speed_y = -*ball_speed_y;
    }

    // Collision avec la raquette
    if (SDL_HasIntersection(ball, paddle)) {
        *ball_speed_y = -*ball_speed_y;
        ball->y = paddle->y - ball->h; // Ajuster pour éviter de rester coincé
    }

    // Si la balle sort de l'écran (en bas)
    if (ball->y > window_height) {
        printf("Game Over!\n");
        ball->x = window_width / 2 - ball->w / 2;
        ball->y = window_height / 2 - ball->h / 2;
        *ball_speed_x = 200.0f * (rand() % 2 == 0 ? 1 : -1);
        *ball_speed_y = 200.0f;
    }
}

void render(SDL_Renderer* renderer, SDL_Rect* paddle, SDL_Rect* ball) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, paddle);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, ball);

    SDL_RenderPresent(renderer);
}

void clean_SDL(SDL_Window* window, SDL_Renderer* renderer) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char *argv[]) {
    int running = 1;
    int window_width = 800;
    int window_height = 600;

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    if (!initialize(&window, &renderer, window_width, window_height)) {
        return -1;
    }

    srand((unsigned)time(NULL));

    SDL_Rect paddle = {window_width / 2 - 60, window_height - 20, 120, 10};
    SDL_Rect ball = {window_width / 2 - 10, window_height / 2 - 10, 20, 20};

    float ball_speed_x = 200.0f * (rand() % 2 == 0 ? 1 : -1);
    float ball_speed_y = 200.0f;

    Uint32 lastTime = SDL_GetTicks();

    while (running) {
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        handle_events(&running, &paddle, window_width);
        update_ball(&ball, &ball_speed_x, &ball_speed_y, &paddle, window_width, window_height);
        render(renderer, &paddle, &ball);

        SDL_Delay(16);
    }

    clean_SDL(window, renderer);
    return 0;
}
