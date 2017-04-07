#ifndef Graphics_hpp
#define Graphics_hpp
#include <SDL2/SDL.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <iostream>

class Graphics {
public:
    bool setup();
    void destroy();
    
    void renderClear()       { SDL_SetRenderDrawColor(rend, 1, 1, 1, 1), SDL_RenderClear(rend); }
    void renderPresent()     { SDL_RenderPresent(rend); }
    SDL_Renderer* renderer() { return rend; }
    int width()              { return WINDOW_WIDTH; }
    
    void renderTexture(SDL_Texture *texture, SDL_Rect* position, SDL_Rect* clip = NULL);
    void renderRotatedTexture(SDL_Texture *texture, SDL_Rect* position, const double angle, const SDL_Point*
                              center, SDL_RendererFlip flip = SDL_FLIP_NONE, SDL_Rect* clip = NULL);
    SDL_Texture* loadTexture(std::string filepath);
    SDL_Texture* renderText(const std::string &message, const std::string &filepath, SDL_Color colour, int fontsize);
    Mix_Chunk* loadSound(std::string filepath);
    Mix_Music* loadMusic(std::string filepath);
private:
    SDL_Renderer* rend = nullptr;
    SDL_Window*   window = nullptr;
    
    const int WINDOW_WIDTH  { 720 };
    const int WINDOW_HEIGHT { 480 };
};

#endif
