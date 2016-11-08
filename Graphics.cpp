#include "Graphics.hpp"
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_image/SDL_image.h>

bool Graphics::setup() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cerr << "Error: init" << SDL_GetError() << std::endl;
        return false;
    }
    
    if (TTF_Init() < 0) {
        std::cerr << "Error: TTF init" << TTF_GetError << std::endl;
        return false;
    }
    
    window = SDL_CreateWindow("Skate Forever", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Error: Create window" << SDL_GetError() << std::endl;
        return false;
    }
    
    
    rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (rend == nullptr) {
        std::cerr << "Error: Create renderer" << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

void Graphics::destroy() {
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(window);
}

SDL_Texture* Graphics::loadTexture(std::string filepath) {
    SDL_Texture* temp = IMG_LoadTexture(rend, filepath.c_str());
    if (temp == nullptr)
        std::cerr << "Error: Load dino texture";
    return temp;
}

void Graphics::renderTexture(SDL_Texture *texture, SDL_Rect position) {
    SDL_RenderCopy(rend, texture, nullptr, &position);
}

SDL_Texture* Graphics::renderText(const std::string &message, const std::string &filepath, SDL_Color colour, int fontsize) {
    TTF_Font *font = TTF_OpenFont(filepath.c_str(), fontsize);
    if (font == nullptr){
        std::cerr << "Error: TTF_OpenFont" << TTF_GetError;
        return nullptr;
    }
    SDL_Surface *surf = TTF_RenderText_Solid(font, message.c_str(), colour);
    if (surf == nullptr){
        TTF_CloseFont(font);
        std::cout << "Error: TTF_RenderText" << TTF_GetError;
        return nullptr;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(rend, surf);
    if (texture == nullptr){
        std::cout << "Error: CreateTexture" << SDL_GetError();
    }

    SDL_FreeSurface(surf);
    TTF_CloseFont(font);
    return texture;
}