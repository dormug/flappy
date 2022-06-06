#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "game.h"
#include "rendering.h"
#include "font.h"

static SDL_Texture *background_texture;
static SDL_Texture *bird_texture;
static SDL_Texture *ground_texture;
static SDL_Texture *tubetop_texture;
static SDL_Texture *tubebody_texture;

void load_textures(SDL_Renderer *renderer) {
    SDL_Surface *loadedSurface = IMG_Load("res/background.png");
    background_texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

    loadedSurface = IMG_Load("res/flappy.png");
    bird_texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

    loadedSurface = IMG_Load("res/ground.png");
    ground_texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

    loadedSurface = IMG_Load("res/tubetop.png");
    tubetop_texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    loadedSurface = IMG_Load("res/tubebody.png");
    tubebody_texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

    SDL_FreeSurface(loadedSurface);
}

void render_bird(SDL_Renderer *renderer, const game_t *game, const bird_t *bird) {
    SDL_Rect srcRect = {
        .x = 0,
        .y = 0,
        .w = 17,
        .h = 12,
    };
    SDL_Rect destRect = {
        .x = SCREEN_WIDTH / 2 - 68 / 2,
        .y = (int) (bird->y_position) - 48 / 2,
        .w = 68,
        .h = 48,
    };

    double rotation = -20;
    if (bird->y_velocity > 9) {
        rotation = (bird->y_velocity - 9) * 15;
    }
    if (game->state == STARTING_STATE) {
        rotation = 0;
    }
    SDL_RenderCopyEx(renderer,
            bird_texture,
            &srcRect,
            &destRect,
            rotation,
            NULL,
            SDL_FLIP_NONE
    );
}

void render_tubes(SDL_Renderer *renderer, const tube_t *tubes) {
    for (int i = 0; i < TUBE_COUNT; i++) {
        SDL_Rect destRect = {
            .x = tubes[i].position - 4,
            .y = SCREEN_HEIGHT - tubes[i].height,
            .w = 96,
            .h = 40,
        };
        SDL_RenderCopy(renderer, tubetop_texture, NULL, &destRect);
        destRect.x = tubes[i].position - 4;
        destRect.y = SCREEN_HEIGHT - tubes[i].height - TUBE_GAP;
        destRect.w = 96;
        destRect.h = -40;
        SDL_RenderCopyEx(renderer, tubetop_texture, NULL, &destRect, 0, NULL, SDL_FLIP_VERTICAL);

        destRect.x = tubes[i].position;
        destRect.y = SCREEN_HEIGHT - tubes[i].height + 40;
        destRect.w = 88;
        destRect.h = tubes[i].height - GROUND_HEIGHT;
        SDL_RenderCopy(renderer, tubebody_texture, NULL, &destRect);

        destRect.x = tubes[i].position;
        destRect.y = 0;
        destRect.w = 88;
        destRect.h = SCREEN_HEIGHT - tubes[i].height - TUBE_GAP - 40;
        SDL_RenderCopy(renderer, tubebody_texture, NULL, &destRect);
    }
}

void render_background(SDL_Renderer *renderer, const game_t *game) {
    SDL_SetRenderDrawColor(renderer, 0x7A, 0xDE, 0x86, 0xFF);
    SDL_Rect destRect = {
        .x = 0,
        .y = 530,
        .w = SCREEN_WIDTH,
        .h = 45,
    };
    SDL_RenderFillRect(renderer, &destRect);
    destRect.x = 0;
    destRect.y = 380;
    destRect.w = SCREEN_WIDTH;
    destRect.h = 160;
    SDL_RenderCopy(renderer, background_texture, NULL, &destRect);
}

void render_ground(SDL_Renderer *renderer, const game_t *game) {
    SDL_SetRenderDrawColor(renderer, 0xD9, 0xD1, 0x8F, 0xFF);
    SDL_Rect destRect = {
        .x = -game->ground_offset,
        .y = SCREEN_HEIGHT - GROUND_HEIGHT,
        .w = SCREEN_WIDTH + 24,
        .h = GROUND_HEIGHT,
    };
    SDL_RenderFillRect(renderer, &destRect);
    destRect.h = 28;
    SDL_RenderCopy(renderer, ground_texture, NULL, &destRect);
}

void render_ui(SDL_Renderer *renderer, const game_t *game) {
    char *score = malloc(32);
    sprintf(score, "%d", game->score);
    render_text_center(renderer, SCREEN_WIDTH / 2, 60, 5, 1, score);
    free(score);
}

void free_textures() {
    SDL_DestroyTexture(background_texture);
    SDL_DestroyTexture(bird_texture);
    SDL_DestroyTexture(ground_texture);
}

void render_game(SDL_Renderer *renderer, const game_t *game) {
    SDL_SetRenderDrawColor(renderer, 0x67, 0xBE, 0xC6, 0xFF); // sky color
    SDL_RenderClear(renderer);

    render_background(renderer, game);
    render_tubes(renderer, game->tubes);
    render_bird(renderer, game, &game->bird);
    render_ground(renderer, game);
    render_ui(renderer, game);

    SDL_RenderPresent(renderer);
}

