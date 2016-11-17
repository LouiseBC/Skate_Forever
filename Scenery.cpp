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

void Scenery::setBackGroundColour(int colour) {
    bgColour = colour;
}

void Scenery::updateBgColour() {
    switch(bgColour) {
        case colour::yellow: if (r != 225) ++r;
                if (g != 170) --g;
                if (b != 170) --b;
            break;
        case colour::blue: if (r != 210) --r;
                           if (g != 180) --g;
                           if (b != 225) ++b;
        default:
            break;
    }
    SDL_SetTextureColorMod( background, r, g, b );
    SDL_SetTextureColorMod( farBuildings, r, g, b );
    SDL_SetTextureColorMod( buildings, r, g, b );
    SDL_SetTextureColorMod( foreground, r, g, b );
}

void Scenery::update(const float &deltaTime, const float& gameSpeed) {
    //updateBgColour();
    
    farBuildingsPos.x -= (int)(farBuildingSpeed * deltaTime * gameSpeed);
    farBuildingsPos2.x -= (int)(farBuildingSpeed * deltaTime * gameSpeed);
    
    buildingsPos.x -= (int)(buildingSpeed * deltaTime * gameSpeed);
    buildingsPos2.x -= (int)(buildingSpeed * deltaTime * gameSpeed);
    
    foregroundPos.x -= (int)(foregroundSpeed * deltaTime * gameSpeed);
    foregroundPos2.x -= (int)(foregroundSpeed * deltaTime * gameSpeed);
    
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
    
    SDL_SetRenderDrawColor(graphics->renderer(), 90, 90, 90, 1);
    SDL_RenderFillRect(graphics->renderer(), &ground);
}