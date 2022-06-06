#ifndef RENDERING_H
#define RENDERING_H

void load_textures(SDL_Renderer *renderer);

void render_game(SDL_Renderer *renderer, const game_t *game);

void free_textures();

#endif // RENDERING_H
