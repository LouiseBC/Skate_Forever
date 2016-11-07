#include "SquareObstacle.hpp"
#include "LowObstacle.hpp"

SquareObstacle::SquareObstacle() {
    positionRects.push_back(SDL_Rect{OFFSCREEN_X, GROUND_Y - 2*BLOCK_SIZE,
                                   BLOCK_SIZE, BLOCK_SIZE}); // [0][0]
    positionRects.push_back(SDL_Rect{OFFSCREEN_X + BLOCK_SIZE + BLOCK_PADDING, GROUND_Y - 2*BLOCK_SIZE,
                                   BLOCK_SIZE, BLOCK_SIZE}); // [1][0]
    positionRects.push_back(SDL_Rect{OFFSCREEN_X, GROUND_Y-3*BLOCK_SIZE-BLOCK_PADDING,
                                   BLOCK_SIZE, BLOCK_SIZE}); // [1][0]
    positionRects.push_back(SDL_Rect{OFFSCREEN_X + BLOCK_SIZE + BLOCK_PADDING, GROUND_Y-3*BLOCK_SIZE - BLOCK_PADDING,
                                   BLOCK_SIZE, BLOCK_SIZE}); // [1][1]
}

SquareObstacle::~SquareObstacle() {
    
}

void SquareObstacle::render(SDL_Renderer* renderer) {
    for (int i = 0; i < positionRects.size(); ++i)
        SDL_RenderFillRect(renderer, &positionRects[i]);
}

void SquareObstacle::move(float deltaTime) {
    for (int i = positionRects.size()-1; i >= 0; --i)
        positionRects[i].x -= MOVE_SPEED * deltaTime;
    if (positionRects[1].x + BLOCK_SIZE < 0)
        isOnscreen = false;
}
