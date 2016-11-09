#ifndef Scenery_hpp
#define Scenery_hpp
#include "Graphics.hpp"
#include <vector>

class Scenery {
public:
    void init(Graphics* graphics);
    void destroy();
    void update(const float& deltaTime);
    void render();
private:
    Graphics* graphics;
    SDL_Texture* background;
    SDL_Texture* farBuildings;
    SDL_Texture* buildings;
    SDL_Texture* foreground;
    
    const int GROUND_X      { 0 };
    const int GROUND_Y      { 429 };
    const int WINDOW_HEIGHT { 480 };
    const int WINDOW_WIDTH  { 720 };
    
    const int farBuildingSpeed { 75 };
    const int buildingSpeed    { 120 };
    const int foregroundSpeed  { 220 };
    
    std::vector<SDL_Rect> positions;

    SDL_Rect ground { GROUND_X, GROUND_Y, WINDOW_WIDTH, WINDOW_HEIGHT-GROUND_Y };
    SDL_Rect backgroundPos { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT + 50 };
    
    SDL_Rect farBuildingsPos { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT + 50 };
    SDL_Rect farBuildingsPos2 { WINDOW_WIDTH, 0, WINDOW_WIDTH, WINDOW_HEIGHT + 50 };
    
    SDL_Rect buildingsPos { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT + 50 };
    SDL_Rect buildingsPos2 { WINDOW_WIDTH, 0, WINDOW_WIDTH, WINDOW_HEIGHT + 50 };
    
    SDL_Rect foregroundPos { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT + 50 };
    SDL_Rect foregroundPos2 { WINDOW_WIDTH, 0, WINDOW_WIDTH, WINDOW_HEIGHT + 50 };
};



#endif
