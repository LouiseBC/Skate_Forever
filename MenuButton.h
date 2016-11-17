#ifndef MenuButton_h
#define MenuButton_h
#include <SDL2/SDL.h>

struct MenuButton {
    SDL_Rect position;
    SDL_Texture* texture;
    
    bool isActive      { false };
    int animationCount { 0 };
    int direction      { 1 };
    int positionChange { 0 };
};

#endif
