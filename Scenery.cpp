#include "Scenery.hpp"
#include "SDL2_image/SDL_image.h"

void Scenery::init(Graphics *graph) {
    graphics = graph;
    
    background = graphics->loadTexture("Assets/background.png");
    farBuildings = graphics->loadTexture("Assets/farbuildings.png");
    buildings = graphics->loadTexture("Assets/buildings.png");
    foreground = graphics->loadTexture("Assets/foreground.png");
}

void Scenery::destroy() {
    graphics = nullptr;
}

void Scenery::update(const float &deltaTime) {
    farBuildingsPos.x -= (int)(farBuildingSpeed * deltaTime);
    farBuildingsPos2.x -= (int)(farBuildingSpeed * deltaTime);
    
    buildingsPos.x -= (int)(buildingSpeed * deltaTime);
    buildingsPos2.x -= (int)(buildingSpeed * deltaTime);
    
    foregroundPos.x -= (int)(foregroundSpeed * deltaTime);
    foregroundPos2.x -= (int)(foregroundSpeed * deltaTime);
    
    if (farBuildingsPos.x + WINDOW_WIDTH < 0)
        farBuildingsPos.x = farBuildingsPos2.x + WINDOW_WIDTH;
    if (farBuildingsPos2.x + WINDOW_WIDTH < 0)
        farBuildingsPos2.x = farBuildingsPos.x +WINDOW_WIDTH;
    
    if (buildingsPos.x + WINDOW_WIDTH < 0)
        buildingsPos.x = buildingsPos2.x + WINDOW_WIDTH;
    if (buildingsPos2.x + WINDOW_WIDTH < 0)
        buildingsPos2.x = buildingsPos.x + WINDOW_WIDTH;
    
    if (foregroundPos.x + WINDOW_WIDTH < 0)
        foregroundPos.x = foregroundPos2.x + WINDOW_WIDTH;
    if (foregroundPos2.x + WINDOW_WIDTH < 0)
        foregroundPos2.x = foregroundPos.x + WINDOW_WIDTH;
}

void Scenery::render() {
    graphics->renderTexture(background, &backgroundPos);
    
    graphics->renderTexture(farBuildings, &farBuildingsPos);
    graphics->renderTexture(farBuildings, &farBuildingsPos2);
    
    graphics->renderTexture(buildings, &buildingsPos);
    graphics->renderTexture(buildings, &buildingsPos2);
    
    graphics->renderTexture(foreground, &foregroundPos);
    graphics->renderTexture(foreground, &foregroundPos2);
    
    //graphics->renderTexture(foreground, &window);
    SDL_SetRenderDrawColor(graphics->renderer(), 90, 90, 90, 1);
    SDL_RenderFillRect(graphics->renderer(), &ground);
}