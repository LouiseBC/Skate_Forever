#include "DuckShortObstacle.hpp"

DuckShortObstacle::DuckShortObstacle() {
    int y = 0;
    
    for (int i = 0; i < 8; ++i) {
        int x = OFFSCREEN_X;
        for (int j = 0; j < 2; ++j) {
            positionRects.push_back(SDL_Rect{x, y, BLOCK_SIZE, BLOCK_SIZE});
            x += BLOCK_SIZE + BLOCK_PADDING;
        }
        y += BLOCK_SIZE + BLOCK_PADDING;
    }
}

DuckShortObstacle::~DuckShortObstacle() {
    
}

void DuckShortObstacle::render(SDL_Renderer* renderer) {
    for (int i = 0; i < positionRects.size(); ++i)
        SDL_RenderFillRect(renderer, &positionRects[i]);
}

void DuckShortObstacle::move(const float& deltaTime) {
    for (int i = positionRects.size()-1; i >= 0; --i)
        positionRects[i].x -= MOVE_SPEED * deltaTime;
    if (positionRects[positionRects.size()-1].x + BLOCK_SIZE < 0)
        isOnscreen = false;
}

void DuckShortObstacle::move(const int &xPos) {
    int count = 0;
    for (int i = 0; i < 8; ++i) {
        int x = xPos;
        for (int j = 0; j < 2; ++j) {
            positionRects[count].x = x;
            x += BLOCK_SIZE + BLOCK_PADDING;
            ++count;
        }
    }
}