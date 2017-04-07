#ifndef Obstacle_hpp
#define Obstacle_hpp
#include "SDL2/SDL.h"
#include <vector>

class Graphics;

class Obstacle {
public:
    virtual ~Obstacle() {};
    
    virtual void move(const float& deltaTime, const float& gameVel) = 0;
    virtual void move(const int& xPos) = 0;
    virtual void render(SDL_Renderer* renderer) = 0;
    
    virtual int  rightSideX() const = 0;
    virtual int  leftSideX()  const = 0;
    virtual int& type() = 0;
    virtual bool& isOnScreen() = 0;
    
    virtual std::vector<SDL_Rect>& positions() = 0;
    enum type                  { low = 0, square, shortduck, longduck };
    
protected:
    const int BLOCK_SIZE       {  42 };
    const int BLOCK_PADDING    {   2 };
    const int GROUND_Y         { 429 };
    const int OFFSCREEN_X      { 720 };
    
    const float MOVE_SPEED     { 300.0f };
};

#endif
