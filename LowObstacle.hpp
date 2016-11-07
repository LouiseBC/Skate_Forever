#ifndef LowObstacle_hpp
#define LowObstacle_hpp
#include "Obstacle.hpp"

class LowObstacle : public Obstacle {
public:
    LowObstacle();
    ~LowObstacle();
    
    void move(float deltaTime);
    void render(SDL_Renderer* renderer);
    
    int type() { return obstacleType; }
    bool isOnScreen() { return isOnscreen; }

private:
    int obstacleType           { type::low };
    bool isOnscreen            { true };
    
    std::vector<SDL_Rect> positionRects;
};

#endif