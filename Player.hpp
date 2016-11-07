#ifndef Player_hpp
#define Player_hpp
#include "Graphics.hpp"

class Player {
public:
    void init(Graphics* graphics);
    void destroy();
    void render();
    void handleEvent(SDL_Event& event, int obstacletype);
    void update(float deltaTime);
    
    void jump(float deltaTime);
    bool isJumping() { return isjumping; }
private:
    Graphics* graphics          = nullptr;
    SDL_Texture* playerStand    = nullptr;
    
    // Render data
    const int SPRITE_WIDTH       { 92 };
    const int SPRITE_HEIGHT      { 108 };
    const int X_POS              { 75 };
    const int Y_POS_DEFAULT      { 320 };
    //int       yPos               { Y_POS_DEFAULT };
    SDL_Rect playerPos { X_POS, Y_POS_DEFAULT, SPRITE_WIDTH, SPRITE_HEIGHT };
    
    // Jump data
    const float Y_VEL_DEFAULT     { -400.0f };
    float  yVelocity              { Y_VEL_DEFAULT };
    float  gravity                { 400.0f };
    bool isjumping              { false };
    int obstacle                { -1 };
};

#endif