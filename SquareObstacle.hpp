#ifndef SquareObstacle_hpp
#define SquareObstacle_hpp
#include "Obstacle.hpp"

class SquareObstacle : public Obstacle {
public:
    SquareObstacle();
    ~SquareObstacle();
    
    void move(const float& deltaTime);
    void move(const int& xPos);
    void render(SDL_Renderer* renderer);
    
    int& type() { return obstacleType; }
    bool& isOnScreen() { return isOnscreen; }
    std::vector<SDL_Rect>& positions() { return positionRects; }
    
private:
    int obstacleType           { type::square };
    bool isOnscreen            { true };
    
    std::vector<SDL_Rect> positionRects;
};

#endif