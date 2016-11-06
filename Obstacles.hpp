#ifndef Obstacles_hpp
#define Obstacles_hpp
//#include "Graphics.hpp"
#include <vector>

class Graphics;
class Obstacle;

class Obstacles {
public:
    void init(Graphics* graphics);
    void destroy();
    
    void update(float deltaTime);
    void render();
    void reset();
    
    int type();
    
private:
    Graphics* graphics = nullptr;
    Obstacle* currentObstacle = nullptr;
};

#endif