#include "SquareObstacle.hpp"

SquareObstacle::SquareObstacle() {
    positionRects.push_back(SDL_Rect{OFFSCREEN_X, GROUND_Y - 2*BLOCK_SIZE,
                                     BLOCK_SIZE, BLOCK_SIZE}); // [0][0]
    positionRects.push_back(SDL_Rect{OFFSCREEN_X + BLOCK_SIZE + BLOCK_PADDING, GROUND_Y - 2*BLOCK_SIZE,
                                     BLOCK_SIZE, BLOCK_SIZE}); // [1][0]
    positionRects.push_back(SDL_Rect{OFFSCREEN_X, GROUND_Y-3*BLOCK_SIZE-BLOCK_PADDING,
                                     BLOCK_SIZE, BLOCK_SIZE}); // [0][1]
    positionRects.push_back(SDL_Rect{OFFSCREEN_X + BLOCK_SIZE + BLOCK_PADDING, GROUND_Y-3*BLOCK_SIZE - BLOCK_PADDING,
                                     BLOCK_SIZE, BLOCK_SIZE}); // [1][1]
}

SquareObstacle::~SquareObstacle() {
    
}

void SquareObstacle::render(SDL_Renderer* renderer) {
    for (int i = 0; i < positionRects.size(); ++i)
        SDL_RenderFillRect(renderer, &positionRects[i]);
}

void SquareObstacle::move(const float& deltaTime, const float& gameVel) {
    for (int i = positionRects.size()-1; i >= 0; --i)
        positionRects[i].x -= MOVE_SPEED * deltaTime * gameVel;
    if (positionRects[1].x + BLOCK_SIZE < 0)
        isOnscreen = false;
}

void SquareObstacle::move(const int &xPos) {
    positionRects[0].x = xPos;
    positionRects[1].x = xPos + BLOCK_SIZE + BLOCK_PADDING;
    positionRects[2].x = xPos;
    positionRects[3].x = xPos + BLOCK_SIZE + BLOCK_PADDING;
}

int SquareObstacle::rightSideX() const {
    return positionRects[positionRects.size()-1].x + positionRects[positionRects.size()-1].w;
}

int SquareObstacle::leftSideX() const {
    return positionRects[0].x;
}