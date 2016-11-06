#ifndef LowObstacle_hpp
#define LowObstacle_hpp
#include "Obstacle.hpp"

class LowObstacle : public Obstacle {
public:
    ~LowObstacle();
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