#ifndef FONT_H
#define FONT_H

#define FONT_WIDTH 8
#define FONT_HEIGHT 12

void init_font(SDL_Renderer *renderer);

void quit_font();

void render_text(SDL_Renderer *renderer, int x, int y, double scale, int spacing, char *text);

void render_text_center(SDL_Renderer *renderer, int x, int y, double scale, int spacing, char *text);

#endif // FONT_H
