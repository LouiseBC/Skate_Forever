#ifndef Player_hpp
#define Player_hpp
#include "Graphics.hpp"
#include <vector>

class Obstacle;

class Player {
public:
    void init(Graphics* graphics);
    void destroy();
    
    void handleEvent(SDL_Event& event, const int& obstacletype);
    void update(const float& deltaTime, Obstacle* currentObstacle, const float& gameSpeed);
    void updateScore(Obstacle* currentObstacle);
    void render();
    void renderScore();
    
    void setJumpType(const int& obstacletype);
    void handleJump(const float& deltaTime, const float& gameSpeed);
    void toggleJumpAnimation();
    
    void checkCollision(Obstacle* currentObstacle);
    void checkSideCollision(std::vector<SDL_Rect> obstacle);
    void checkTopCollision(std::vector<SDL_Rect> obstacle);
    void checkBottomCollision(std::vector<SDL_Rect> obstacle);
    void isOnObstacle(std::vector<SDL_Rect> obstacle);
    
    int  status() const { return currentState; }
    int  score() const { return currentScore; }
    enum state { dead = 0, onGround, inAir, ducking, onObstacle };
        
private:
    // Player variables
    int  currentState  { state::onGround };
    int  currentScore  { 0 };
    int  highScore     { 0 };
    
    // Movement data
    float yVelocity;
    float gravity;
    int   obstacleType { -1 };
    
    // Player rendering data
    const int X_POS                   { 75 };
    const int Y_POS_DEFAULT           { 320 };
    
    const int SPRITE_WIDTH            { 92 };
    const int SPRITE_HEIGHT           { 108 };
    const int SPRITE_HEIGHT_DUCK      { 65 };
    const int SKATEBOARD_HEIGHT       { 16 };
    
    const int BACK_HEAD_OFFSET        { 35 };
    const int FRONT_SKATEBOARD_OFFSET { 6 };
    const int BACK_SKATEBOARD_OFFSET  { 10 };
    
    Graphics* graphics            { nullptr };
    SDL_Texture* renderTexture    { nullptr };
    SDL_Texture* playerStand      { nullptr };
    SDL_Texture* playerDuck       { nullptr };
    
    SDL_Rect playerPos     { X_POS, Y_POS_DEFAULT, SPRITE_WIDTH, SPRITE_HEIGHT }; // player + skateboard
    SDL_Rect playerClip    { 0, 0, SPRITE_WIDTH, SPRITE_HEIGHT };
    SDL_Rect skateBoardClip{ 0, SPRITE_HEIGHT - SKATEBOARD_HEIGHT, SPRITE_WIDTH, SKATEBOARD_HEIGHT}; // only skateboard
    SDL_Rect skateBoardPos { X_POS, Y_POS_DEFAULT + SPRITE_HEIGHT - SKATEBOARD_HEIGHT, SPRITE_WIDTH, SKATEBOARD_HEIGHT };
    
    // Score rendering
    SDL_Texture* scoreTexture { nullptr };
    bool scoreUpdated  { false };
};

#endif