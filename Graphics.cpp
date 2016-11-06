#include "Graphics.hpp"


void Graphics::setup() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        std::cerr << "Error: init" << SDL_GetError() << std::endl;
    
    else {
        window = SDL_CreateWindow("Skate Forever", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                   WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == nullptr)
            std::cerr << "Error: Create window" << SDL_GetError() << std::endl;
        
        else {
            rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (rend == nullptr)
                std::cerr << "Error: Create renderer" << SDL_GetError() << std::endl;
        }
    }
}

void Graphics::destroy() {
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(window);
}

void Graphics::renderTexture(SDL_Texture *texture, SDL_Rect position) {
    SDL_RenderCopy(rend, texture, nullptr, &position);
}