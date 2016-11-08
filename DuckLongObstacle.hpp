#ifndef DuckLongObstacle_hpp
#define DuckLongObstacle_hpp
#include "Obstacle.hpp"

class DuckLongObstacle : public Obstacle {
public:
    DuckLongObstacle();
    ~DuckLongObstacle();
    
    void move(const float& deltaTime);
    void move(const int& xPos);
    void render(SDL_Renderer* renderer);
    
    int& type() { return obstacleType; }
    bool& isOnScreen() { return isOnscreen; }
    std::vector<SDL_Rect>& positions() { return positionRects; }
    
private:
    int obstacleType           { type::ducklong };
    bool isOnscreen            { true };
    
    std::vector<SDL_Rect> positionRects;
};

#endif