#ifndef GAME_H
#define GAME_H

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 640

#define SPEED 3
#define GROUND_HEIGHT 80

enum game_states {
    STARTING_STATE,
    RUNNING_STATE,
    GAME_OVER_STATE,
    QUIT_STATE,
};

#define TUBE_WIDTH 88
#define TUBE_GAP 175
#define TUBE_COUNT 2
#define TUBE_MIN_HEIGHT 150
#define TUBE_MAX_HEIGHT 250

typedef struct {
    int position;
    int height;
} tube_t;

#define BIRD_WIDTH 52
#define BIRD_HEIGHT 32

typedef struct {
    const int JUMP_VELOCITY;
    const double GRAVITY;
    const int MAX_VELOCITY;
    double y_position;
    double y_velocity;
    double rotation;
    bool isJumping;
    bool isColliding;
} bird_t;

typedef struct {
    bird_t bird;
    int state;
    int score;
    tube_t *tubes;
    int ground_offset;
    SDL_Renderer *renderer;
} game_t;


#endif // GAME_H

