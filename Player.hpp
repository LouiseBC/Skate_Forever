#ifndef Player_hpp
#define Player_hpp
#include "Graphics.hpp"

class Obstacle;

class Player {
public:
    void init(Graphics* graphics);
    void destroy();
    
    void handleEvent(SDL_Event& event, const int& obstacletype);
    void update(const float& deltaTime, Obstacle* currentObstacle);
    void updateScore(Obstacle* currentObstacle);
    void render();
    void renderScore();
    
    void setJumpType(const int& obstacletype);
    void handleJump(const float& deltaTime);
    void toggleJumpAnimation();
    
    void checkCollision(Obstacle* currentObstacle);
    void isOnObstacle(Obstacle* currentObstacle);
    
    int status() const { return currentState; }
    enum state { dead = 0, onGround, inAir, ducking, onObstacle };
        
private:
    Graphics* graphics            { nullptr };
    SDL_Texture* renderTexture    { nullptr };
    SDL_Texture* playerStand      { nullptr };
    SDL_Texture* playerDuck       { nullptr };
    
    // Player variables
    int  currentState  { state::onGround };
    bool isDead        { false };
    int  currentScore  { 0 };
    int  highScore     { 0 };
    // Score rendering
    SDL_Texture* score { nullptr };
    bool scoreUpdated  { false };
    
    // Player rendering data
    const int X_POS                  { 75 };
    const int Y_POS_DEFAULT          { 320 };
    
    const int SPRITE_WIDTH           { 92 };
    const int SPRITE_HEIGHT          { 108 };
    const int SPRITE_HEIGHT_DUCK     { 65 };
    const int DUCK_OFFSET            { 43 };
    const int BACK_HEAD_OFFSET       { 35 };
    
    const int SKATEBOARD_OFFSET      { 6 };
    const int BACK_SKATEBOARD_OFFSET { 10 };
    const int SKATEBOARD_HEIGHT      { 16 };
    
    SDL_Rect playerPos     { X_POS, Y_POS_DEFAULT, SPRITE_WIDTH, SPRITE_HEIGHT };
    SDL_Rect playerClip    { 0, 0, SPRITE_WIDTH, SPRITE_HEIGHT };
    SDL_Rect skateBoardClip{ 0, SPRITE_HEIGHT - SKATEBOARD_HEIGHT, SPRITE_WIDTH, SKATEBOARD_HEIGHT};
    SDL_Rect skateBoardPos { X_POS, Y_POS_DEFAULT + SPRITE_HEIGHT - SKATEBOARD_HEIGHT, SPRITE_WIDTH, SKATEBOARD_HEIGHT };
    
    // Movement data
    float yVelocity;
    float gravity;
    int   obstacleType { -1 };
};

#endif