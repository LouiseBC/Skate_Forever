#ifndef Obstacle_hpp
#define Obstacle_hpp
#include "Graphics.hpp"
#include <vector>

class Obstacle {
public:
    void init(Graphics* graphics);
    void destroy();
    void loadObstacle(int obstacletype);
    void update(float deltaTime);
    void render();
    
    void move(float deltaTime);
    void reset();
    int  obstacleType() { return obstacletype; }
private:
    Graphics* graphics = nullptr;
    
    const int BLOCK_SIZE       {  42 };
    const int BLOCK_PADDING    {   2 };
    const int OBSTACLE_WIDTH   {  88 };
    const int OBSTACLE_HEIGHT  {  88 };
    const int GROUND_Y         { 429 };
    const int OFFSCREEN_X      { 720 };
    
    float MOVE_SPEED           { 250.0f};
    
    enum type                  { low = 0, square };
    int obstacletype           { type::low };
    bool isonscreen              { true };
    
    SDL_Rect obstacle_low[2];
    SDL_Rect obstacle_square[4];
};

#endif
