#include <stdbool.h>
#include <string.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "game.h"
#include "font.h"

static SDL_Texture *bitmap;

void init_font(SDL_Renderer *renderer) {
    SDL_Surface *loadedSurface = IMG_Load("res/font.png");
    bitmap = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);
}

void quit_font() {
    SDL_DestroyTexture(bitmap);
    bitmap = NULL;
}

void render_char(SDL_Renderer *renderer, int x, int y, double scale, char ch) {
    if (ch >= 48 && ch <= 57) { // 0-9
        SDL_Rect srcRect = {
            .x = FONT_WIDTH * (ch - 48),
            .y = 0,
            .w = FONT_WIDTH,
            .h = FONT_HEIGHT,
        };
        SDL_Rect destRect = {
            .x = x,
            .y = y,
            .w = FONT_WIDTH * scale,
            .h = FONT_HEIGHT * scale,
        };
        SDL_RenderCopy(renderer, bitmap, &srcRect, &destRect);
    }
}

// spacing is affected by scale
void render_text(SDL_Renderer *renderer, int x, int y, double scale, int spacing, char *text) {
    int index = 0;
    char ch = text[index];
    while (ch != '\0') {
        render_char(renderer, x + (FONT_WIDTH + spacing) * scale * index, y, scale, ch);
        ch = text[++index];
    }
}

void render_text_center(SDL_Renderer *renderer, int x, int y, double scale, int spacing, char *text) {
    int length = strlen(text);
    double centered = FONT_WIDTH * length;
    centered += spacing * (length - 1);
    centered *= scale / 2;
    centered = x - centered;
    /* printf("stringlen = %d\n", length); */
    /* printf("centered = %f\n", centered); */
    render_text(renderer, centered, y, scale, spacing, text);
}

