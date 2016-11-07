#include "Obstacles.hpp"
#include "LowObstacle.hpp"
#include "SquareObstacle.hpp"
#include "Graphics.hpp"
#include <random>

void Obstacles::init(Graphics *graph) {
    graphics = graph;
    currentObstacle = new LowObstacle;
}

void Obstacles::destroy() {
    graphics = nullptr;
    delete currentObstacle;
    currentObstacle = nullptr;
}

void Obstacles::update(float deltaTime) {
    if (currentObstacle->isOnScreen())
        currentObstacle->move(deltaTime);
    else reset();
}

void Obstacles::reset() {
    delete currentObstacle;
    
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> range(0, 1);
    
    // select a new random obstacle
    int random = range(rd);
    switch(random) {
        case 0: currentObstacle = new LowObstacle;
            break;
        case 1: currentObstacle = new SquareObstacle;
            break;
    }
}

void Obstacles::render() {
    SDL_SetRenderDrawColor(graphics->renderer(), 70, 138, 201, 1);
    currentObstacle->render(graphics->renderer());
}

int Obstacles::type() {
    return currentObstacle->type();
}