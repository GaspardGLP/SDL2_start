#define SDL_MAIN_HANDLED
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>

int initialize(SDL_Window** window, SDL_Renderer** renderer, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not be initialized %s\n", SDL_GetError());
        return 0;
    }

    *window = SDL_CreateWindow("DVD Logo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
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

void events_handling(int* running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            *running = 0;
        }
    }
}

void update_logo_position(SDL_Rect* logo, float* speed_x, float* speed_y, int window_width, int window_height, Uint8* r, Uint8* g, Uint8* b, float deltaTime) {
    logo->x += (int)(*speed_x * deltaTime);
    logo->y += (int)(*speed_y * deltaTime);

    if (logo->x <= 0 || logo->x + logo->w >= window_width) {
        *speed_x = -*speed_x;
        *r = (Uint8)(rand() % 256);
        *g = (Uint8)(rand() % 256);
        *b = (Uint8)(rand() % 256);
    }

    if (logo->y <= 0 || logo->y + logo->h >= window_height) {
        *speed_y = -*speed_y;
        *r = (Uint8)(rand() % 256);
        *g = (Uint8)(rand() % 256);
        *b = (Uint8)(rand() % 256);
    }
}

void render_logo(SDL_Renderer* renderer, SDL_Rect* logo, Uint8 r, Uint8 g, Uint8 b) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderFillRect(renderer, logo);
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

    float speed_x = 200.0f;
    float speed_y = 200.0f;

    Uint8 r = 255, g = 255, b = 255;

    SDL_Rect logo;

    logo.w = 100;
    logo.h = 50;
    logo.x = window_width / 2 - logo.w / 2;
    logo.y = window_height / 2 - logo.h / 2;

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    if (!initialize(&window, &renderer, window_width, window_height)) {
        return -1;
    }

    srand((unsigned)time(NULL));

    Uint32 lastTime = SDL_GetTicks();

    while (running) {
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        events_handling(&running);
        update_logo_position(&logo, &speed_x, &speed_y, window_width, window_height, &r, &g, &b, deltaTime);
        render_logo(renderer, &logo, r, g, b);
        SDL_Delay(16);
    }

    clean_SDL(window, renderer);
    return 0;
}
