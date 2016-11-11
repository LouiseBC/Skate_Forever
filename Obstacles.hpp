#ifndef Obstacles_hpp
#define Obstacles_hpp
#include <vector>

class Graphics;
class Obstacle;

class Obstacles {
public:
    void init(Graphics* graphics);
    void destroy();
    
    void update(const float& deltaTime, const float& gameVel);
    void render();
    void reset(const float& gameVel);
    int getNewObstacleType();
    Obstacle* getNewObstacle();
    void pushObstacle(int obstacleType);
    
    int type();
    Obstacle* current();
    
private:
    //float gameSpeed;
    int   forcedObstacle   { -1 };
    int   previousObstacle { -1 };
    const int WINDOW_WIDTH  { 720 };
    
    Graphics* graphics = nullptr;
    Obstacle* currentObstacle = nullptr;
    Obstacle* nextObstacle = nullptr;
};

#endif