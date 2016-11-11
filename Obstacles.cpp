#include "Obstacles.hpp"
#include "LowObstacle.hpp"
#include "SquareObstacle.hpp"
#include "DuckLongObstacle.hpp"
#include "DuckShortObstacle.hpp"
#include "Graphics.hpp"
#include <random>

void Obstacles::init(Graphics *graph) {
    graphics = graph;
    currentObstacle = new SquareObstacle;
}

void Obstacles::destroy() {
    graphics = nullptr;
    delete currentObstacle;
    delete nextObstacle;
    currentObstacle = nullptr;
    nextObstacle = nullptr;
}

void Obstacles::update(const float& deltaTime, const float& gameVel) {
    if (currentObstacle->isOnScreen())
        currentObstacle->move(deltaTime, gameVel);
    else reset(gameVel);
    

    if (nextObstacle == nullptr && currentObstacle->leftSideX() <= WINDOW_WIDTH/2){
        nextObstacle = new LowObstacle;
        nextObstacle->move(currentObstacle->rightSideX() + WINDOW_WIDTH/2);
    }
    
    if (nextObstacle != nullptr) {
        if (nextObstacle->isOnScreen())
            nextObstacle->move(deltaTime, gameVel);
    }
}

void Obstacles::reset(const float& gameVel) {
    delete currentObstacle;
    currentObstacle = nextObstacle;
    int obstacletype = getNewObstacleType();
        
    switch(obstacletype) {
        case 0: nextObstacle = new LowObstacle;
            break;
        case 1: nextObstacle = new SquareObstacle;
            break;
        case 2: nextObstacle = new DuckShortObstacle;
            break;
        case 3: nextObstacle = new DuckLongObstacle;
            break;
    }
}

int Obstacles::getNewObstacleType() {
    int obstacletype = -1;
    if (forcedObstacle >= 0) {
        obstacletype = forcedObstacle;
        forcedObstacle = -1;
    }
    
    else {
        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_int_distribution<int> range(0, 2);
        obstacletype = range(rd);
        if (previousObstacle == obstacletype) {
            while (previousObstacle == obstacletype)
                obstacletype = range(rd);
        }
    }
    previousObstacle = obstacletype;
    return obstacletype;
}

void Obstacles::pushObstacle(int obstacleType) {
    forcedObstacle = obstacleType;
}

void Obstacles::render() {
    SDL_SetRenderDrawColor(graphics->renderer(), 221, 209, 0, 1);
    currentObstacle->render(graphics->renderer());
    if (nextObstacle != nullptr)
        nextObstacle->render(graphics->renderer());
}

int Obstacles::type() {
    return currentObstacle->type();
}

Obstacle* Obstacles::current() {
    return currentObstacle;
}