#ifndef LowObstacle_hpp
#define LowObstacle_hpp
#include "Obstacle.hpp"

class LowObstacle : public Obstacle {
public:
    LowObstacle();
    ~LowObstacle();
    
    void move(const float& deltaTime);
    void move(const int& xPos);
    void render(SDL_Renderer* renderer);
    
    int& type() { return obstacleType; }
    bool& isOnScreen() { return isOnscreen; }
    std::vector<SDL_Rect>& positions() { return positionRects; }

private:
    int obstacleType           { type::low };
    bool isOnscreen            { true };
    
    std::vector<SDL_Rect> positionRects;
};

#endif