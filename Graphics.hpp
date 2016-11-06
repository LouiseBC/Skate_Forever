#ifndef Graphics_hpp
#define Graphics_hpp
#include "SDL2/SDL.h"
#include <iostream>

class Graphics {
public:
    void setup();
    void destroy();
    
    void renderClear()       {SDL_SetRenderDrawColor(rend, 225, 225, 225, 225), SDL_RenderClear(rend);}
    void renderPresent()     {SDL_RenderPresent(rend);}
    SDL_Renderer* renderer() { return rend; };
    
    void renderTexture(SDL_Texture *texture, SDL_Rect position);
private:
    SDL_Renderer* rend = nullptr;
    SDL_Window*   window = nullptr;
    
    const int WINDOW_HEIGHT { 480 };
    const int WINDOW_WIDTH  { 720 };
};

#endif
