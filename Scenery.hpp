#ifndef Scenery_hpp
#define Scenery_hpp
#include "Graphics.hpp"
#include <vector>

class Scenery {
public:
    void init(Graphics* graphics);
    void destroy();
    
    void update(const float& deltaTime, const float& gameSpeed);
    void render();
    void restart();
private:
    const int farBuildingSpeed { 75 };
    const int buildingSpeed    { 120 };
    const int foregroundSpeed  { 220 };
    
    Graphics* graphics;
    SDL_Texture* background;
    SDL_Texture* farBuildings;
    SDL_Texture* buildings;
    SDL_Texture* foreground;
    
    const int GROUND_X      { 0 };
    const int GROUND_Y      { 429 };
    const int WINDOW_HEIGHT { 480 };
    const int WINDOW_WIDTH  { 720 };

    SDL_Rect ground;
    SDL_Rect backgroundPos;
    
    SDL_Rect farBuildingsPos;
    SDL_Rect farBuildingsPos2;
    
    SDL_Rect buildingsPos;
    SDL_Rect buildingsPos2;
    
    SDL_Rect foregroundPos;
    SDL_Rect foregroundPos2;
};



#endif
