#include "Scenery.hpp"
#include "SDL2_image/SDL_image.h"

void Scenery::init(Graphics *graph) {
    graphics = graph;
}

void Scenery::destroy() {
    graphics = nullptr;
}

void Scenery::render() {
    SDL_SetRenderDrawColor(graphics->renderer(), 80, 80, 80, 1);
    SDL_RenderFillRect(graphics->renderer(), &ground);
}