#ifndef SquareObstacle_hpp
#define SquareObstacle_hpp
#include "Obstacle.hpp"

class SquareObstacle : public Obstacle {
public:
    ~SquareObstacle();
    void init();
    
    void move(float deltaTime);
    void render(SDL_Renderer* renderer);
    
    int type() { return obstacletype; }
    bool isOnScreen() { return isonscreen; }
    
private:
    int obstacletype           { type::low };
    bool isonscreen            { true };
    
    SDL_Rect obstaclePosition[2];
};

#endif
