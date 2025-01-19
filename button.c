#include <string.h>
#include "include/button.h"
#include "include/init.h"
#include "include/events.h"
#include "include/game_logic.h"
#include "include/render.h"
#include "include/menu.h"
#include "include/score.h"
#include "include/utils.h"

// Rendu d'un bouton
void render_button(SDL_Renderer* renderer, TTF_Font* font, Button* button) {
    // Dessiner le rectangle du bouton
    SDL_SetRenderDrawColor(renderer, button->color.r, button->color.g, button->color.b, 255);
    SDL_RenderFillRect(renderer, &button->rect);

    // Dessiner le contour du bouton
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &button->rect);

    // Rendu du texte du bouton
    render_text(renderer, font, button->text, button->rect.x + 10, button->rect.y + 10, button->text_color);
}

// Vérifie si un bouton a été cliqué
int is_button_clicked(Button* button, int mouse_x, int mouse_y) {
    return mouse_x >= button->rect.x &&
           mouse_x <= button->rect.x + button->rect.w &&
           mouse_y >= button->rect.y &&
           mouse_y <= button->rect.y + button->rect.h;
}