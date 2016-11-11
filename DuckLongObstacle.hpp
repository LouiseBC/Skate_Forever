#ifndef DuckLongObstacle_hpp
#define DuckLongObstacle_hpp
#include "Obstacle.hpp"

class DuckLongObstacle : public Obstacle {
public:
    DuckLongObstacle();
    ~DuckLongObstacle();
    
    void move(const float& deltaTime, const float& gameVel);
    void move(const int& xPos);
    void render(SDL_Renderer* renderer);
    
    int  rightSideX() const;
    int  leftSideX()  const;
    int& type() { return obstacleType; }
    bool& isOnScreen() { return isOnscreen; }
    std::vector<SDL_Rect>& positions() { return positionRects; }
    
private:
    int obstacleType           { type::longduck };
    bool isOnscreen            { true };
    
    std::vector<SDL_Rect> positionRects;
};

#endif