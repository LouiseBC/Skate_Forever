#ifndef Obstacle_hpp
#define Obstacle_hpp
#include "SDL2/SDL.h"
#include <vector>

class Graphics;

class Obstacle {
public:
    virtual ~Obstacle() {};
    
    virtual void move(float deltaTime) = 0;
    virtual void render(SDL_Renderer* renderer) = 0;
    
    virtual int type() = 0;
    virtual bool isOnScreen() = 0;
    
protected:
    const int BLOCK_SIZE       {  42 };
    const int BLOCK_PADDING    {   2 };
    const int GROUND_Y         { 429 };
    const int OFFSCREEN_X      { 720 };
    
    const float MOVE_SPEED     { 300.0f };
    enum type                  { low = 0, square };
    
};

#endif
