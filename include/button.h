#ifndef BUTTON_H
#define BUTTON_H

#include <SDL.h>
#include <SDL_ttf.h>

// Structure représentant un bouton
typedef struct Button {
    SDL_Rect rect;         // Zone du bouton
    SDL_Color color;       // Couleur par défaut
    SDL_Color hover_color; // Couleur au survol
    SDL_Color text_color;  // Couleur du texte
    char text[50];         // Texte du bouton
    int is_hovered;        // Indique si le bouton est survolé
} Button;

// Fonctions liées aux boutons
void render_button(SDL_Renderer* renderer, TTF_Font* font, Button* button);
int is_button_clicked(Button* button, int mouse_x, int mouse_y);

#endif // BUTTON_H
