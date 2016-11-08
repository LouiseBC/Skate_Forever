#include "LowObstacle.hpp"
#include <iostream>

LowObstacle::LowObstacle() {
    positionRects.push_back(SDL_Rect{OFFSCREEN_X, GROUND_Y-BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE});
    positionRects.push_back(SDL_Rect{OFFSCREEN_X + BLOCK_SIZE + BLOCK_PADDING, GROUND_Y-BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE});
}

LowObstacle::~LowObstacle() {
    
}

void LowObstacle::render(SDL_Renderer* renderer) {
    for (int i = 0; i < positionRects.size(); ++i)
        SDL_RenderFillRect(renderer, &positionRects[i]);
}

void LowObstacle::move(const float& deltaTime) {
    positionRects[0].x -= MOVE_SPEED * deltaTime;
    positionRects[1].x -= MOVE_SPEED * deltaTime;
    if (positionRects[1].x + BLOCK_SIZE < 0)
        isOnscreen = false;
}

void LowObstacle::move(const int& xPos) {
    positionRects[0].x = xPos;
    positionRects[1].x = xPos + BLOCK_SIZE + BLOCK_PADDING;
}
