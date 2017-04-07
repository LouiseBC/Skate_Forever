#include "Obstacle.hpp"
#include <random>

void Obstacle::init(Graphics *graph) {
    graphics = graph;
    
    loadObstacle(type::low);
    loadObstacle(type::square);
}

void Obstacle::destroy() {
    graphics = nullptr;
}

void Obstacle::loadObstacle(int obstacletype) {
    switch(obstacletype) {
        case type::low:
            obstacle_low[0] = SDL_Rect{OFFSCREEN_X, GROUND_Y-BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE};
            obstacle_low[1] = SDL_Rect{OFFSCREEN_X + BLOCK_SIZE + BLOCK_PADDING, GROUND_Y-BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE};
            break;
        case type::square:
            obstacle_square[0] = SDL_Rect{OFFSCREEN_X, GROUND_Y - 2*BLOCK_SIZE,
                                          BLOCK_SIZE, BLOCK_SIZE}; // [0][0]
            obstacle_square[1] = SDL_Rect{OFFSCREEN_X + BLOCK_SIZE + BLOCK_PADDING, GROUND_Y - 2*BLOCK_SIZE,
                                          BLOCK_SIZE, BLOCK_SIZE}; // [1][0]
            obstacle_square[2] = SDL_Rect{OFFSCREEN_X, GROUND_Y-3*BLOCK_SIZE-BLOCK_PADDING,
                                          BLOCK_SIZE, BLOCK_SIZE}; // [1][0]
            obstacle_square[3] = SDL_Rect{OFFSCREEN_X + BLOCK_SIZE + BLOCK_PADDING, GROUND_Y-3*BLOCK_SIZE - BLOCK_PADDING,
                                          BLOCK_SIZE, BLOCK_SIZE}; // [1][1]
            break;
    }
}

void Obstacle::update(float deltaTime) {
    if (isonscreen)
        move(deltaTime);
    else reset();
}

void Obstacle::reset() {
    // reset current obstacle position
    loadObstacle(obstacletype);
    
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> range(0, 1);
    
    // select a new random obstacle
    int random = range(rd);
    obstacletype = random;
    isonscreen = true;
}

void Obstacle::render() {
    SDL_SetRenderDrawColor(graphics->renderer(), 70, 138, 201, 1);
    switch(obstacletype) {
        case type::low: SDL_RenderFillRects(graphics->renderer(), obstacle_low, 2);
            break;
        case type::square: SDL_RenderFillRects(graphics->renderer(), obstacle_square, 4);
            break;
    }
}

void Obstacle::move(float deltaTime) {
    switch(obstacletype) {
        case type::low:
            for (int i = sizeof(obstacle_low); i >= 0; --i)
                obstacle_low[i].x -= MOVE_SPEED * deltaTime;
            if (obstacle_low[1].x + BLOCK_SIZE < 0)
                isonscreen = false;
            break;
        case type::square:
            for (int i = sizeof(obstacle_square); i >= 0; --i)
                obstacle_square[i].x -= MOVE_SPEED*deltaTime;
            if (obstacle_square[1].x + BLOCK_SIZE < 0)
                isonscreen = false;
            break;
    }
}