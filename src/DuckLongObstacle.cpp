#include "DuckLongObstacle.hpp"

DuckLongObstacle::DuckLongObstacle() {
    int y = 0;
    
    for (int i = 0; i < 8; ++i) {
        int x = OFFSCREEN_X;
        for (int j = 0; j < 15; ++j) {
            positionRects.push_back(SDL_Rect{x, y, BLOCK_SIZE, BLOCK_SIZE});
            x += BLOCK_SIZE + BLOCK_PADDING;
        }
        y += BLOCK_SIZE + BLOCK_PADDING;
    }
}

DuckLongObstacle::~DuckLongObstacle() {
    
}

void DuckLongObstacle::render(SDL_Renderer* renderer) {
    for (int i = 0; i < positionRects.size(); ++i)
        SDL_RenderFillRect(renderer, &positionRects[i]);
}

void DuckLongObstacle::move(const float& deltaTime, const float& gameVel) {
    for (int i = positionRects.size()-1; i >= 0; --i)
        positionRects[i].x -= MOVE_SPEED * deltaTime * gameVel;
    if (positionRects[positionRects.size()-1].x + BLOCK_SIZE < 0)
        isOnscreen = false;
}

void DuckLongObstacle::move(const int &xPos) {
    int count = 0;
    for (int i = 0; i < 8; ++i) {
        int x = xPos;
        for (int j = 0; j < 15; ++j) {
            positionRects[count].x = x;
            x += BLOCK_SIZE + BLOCK_PADDING;
            ++count;
        }
    }
}

int DuckLongObstacle::rightSideX() const {
    return positionRects[positionRects.size()-1].x + positionRects[positionRects.size()-1].w;
}

int DuckLongObstacle::leftSideX() const {
    return positionRects[0].x;
}
