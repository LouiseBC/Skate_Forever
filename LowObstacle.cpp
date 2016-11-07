#include "LowObstacle.hpp"
#include <iostream>

LowObstacle::LowObstacle() {
    positionRects.push_back(SDL_Rect{OFFSCREEN_X, GROUND_Y-BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE});
    positionRects.push_back(SDL_Rect{OFFSCREEN_X + BLOCK_SIZE + BLOCK_PADDING, GROUND_Y-BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE});
    std::cerr << positionRects.size();
}

LowObstacle::~LowObstacle() {
    
}

void LowObstacle::render(SDL_Renderer* renderer) {
    for (int i = 0; i < positionRects.size(); ++i)
        SDL_RenderFillRect(renderer, &positionRects[i]);
}

void LowObstacle::move(float deltaTime) {
    for (int i = positionRects.size()-1; i >= 0; --i)
        positionRects[i].x -= MOVE_SPEED * deltaTime;
    if (positionRects[1].x + BLOCK_SIZE < 0)
        isOnscreen = false;
}
