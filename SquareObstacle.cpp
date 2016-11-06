#include "SquareObstacle.hpp"
#include "LowObstacle.hpp"

void SquareObstacle::init() {
    obstaclePosition[0] = SDL_Rect{OFFSCREEN_X, GROUND_Y - 2*BLOCK_SIZE,
        BLOCK_SIZE, BLOCK_SIZE}; // [0][0]
    obstaclePosition[1] = SDL_Rect{OFFSCREEN_X + BLOCK_SIZE + BLOCK_PADDING, GROUND_Y - 2*BLOCK_SIZE,
        BLOCK_SIZE, BLOCK_SIZE}; // [1][0]
    obstaclePosition[2] = SDL_Rect{OFFSCREEN_X, GROUND_Y-3*BLOCK_SIZE-BLOCK_PADDING,
        BLOCK_SIZE, BLOCK_SIZE}; // [1][0]
    obstaclePosition[3] = SDL_Rect{OFFSCREEN_X + BLOCK_SIZE + BLOCK_PADDING, GROUND_Y-3*BLOCK_SIZE - BLOCK_PADDING,
        BLOCK_SIZE, BLOCK_SIZE}; // [1][1]
}

SquareObstacle::~SquareObstacle() {
    
}

void SquareObstacle::render(SDL_Renderer* renderer) {
    SDL_RenderFillRects(renderer, obstaclePosition, 2);
}

void SquareObstacle::move(float deltaTime) {
    for (int i = sizeof(obstaclePosition); i >= 0; --i)
        obstaclePosition[i].x -= MOVE_SPEED*deltaTime;
    if (obstaclePosition[1].x + BLOCK_SIZE < 0)
        isonscreen = false;
}
