#include "LowObstacle.hpp"

void LowObstacle::init() {
    obstaclePosition[0] = SDL_Rect{OFFSCREEN_X, GROUND_Y-BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE};
    obstaclePosition[1] = SDL_Rect{OFFSCREEN_X + BLOCK_SIZE + BLOCK_PADDING, GROUND_Y-BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE};
}

LowObstacle::~LowObstacle() {
    
}

void LowObstacle::render(SDL_Renderer* renderer) {
    SDL_RenderFillRects(renderer, obstaclePosition, 2);
}

void LowObstacle::move(float deltaTime) {
    for (int i = sizeof(obstaclePosition); i >= 0; --i)
        obstaclePosition[i].x -= MOVE_SPEED * deltaTime;
    if (obstaclePosition[1].x + BLOCK_SIZE < 0)
        isonscreen = false;
}
