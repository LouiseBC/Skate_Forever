#ifndef Scenery_hpp
#define Scenery_hpp
#include "Graphics.hpp"

class Scenery {
public:
    void init(Graphics* graphics);
    void destroy();
    void render();
private:
    Graphics* graphics;
    
    const int GROUND_X      { 0 };
    const int GROUND_Y      { 429 };
    const int WINDOW_HEIGHT { 480 };
    const int WINDOW_WIDTH  { 720 };

    SDL_Rect ground { GROUND_X, GROUND_Y, WINDOW_WIDTH, WINDOW_HEIGHT-321 };
};



#endif
