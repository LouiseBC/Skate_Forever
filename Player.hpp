#ifndef Player_hpp
#define Player_hpp
#include "Graphics.hpp"
#include <SDL2_mixer/SDL_mixer.h>
#include <vector>

class Obstacle;

class Player {
public:
    void init(Graphics* graphics);
    void destroy();
    
    void handleEvent(SDL_Event& event, const int& obstacletype);
    void update(const float& deltaTime, Obstacle* currentObstacle, const float& gameSpeed);
    void render();
    void restart();
    
    void duck();
    void stopDucking();
    
    void setJumpHeight(const int& obstacletype);
    void handleJump(const float& deltaTime, const float& gameSpeed);
    void handleLowJump();
    void handleHighJump(const float& deltaTime, const float& gameSpeed);
    void handleLanding();
    
    void jiggleSkateboard();
    
    void updateScore(Obstacle* currentObstacle);
    void updateShadows(const float& deltaTime);
    
    void checkCollision(Obstacle* currentObstacle);
    void checkSideCollision(std::vector<SDL_Rect> obstacle);
    void checkTopCollision(std::vector<SDL_Rect> obstacle);
    void checkBottomCollision(std::vector<SDL_Rect> obstacle);
    void isOnObstacle(std::vector<SDL_Rect> obstacle);
    
    bool getState() const;
    int  score() const { return currentScore; }
    enum state { dead = 0, onGround, inAir, ducking, onObstacle };
        
private:
    // Player variables
    int  currentState  { state::onGround };
    int  currentScore  { 0 };
    int  highScore     { 0 };
    bool scoreUpdated  { false };
    
    // Movement data
    float yVelocity;
    float gravity;
    int   obstacleType { -1 };
    
    // Skateboard Jiggle data
    int   frameCount   { 0 };
    int   direction    { 1 };
    int   movedAmount  { 0 };
    bool  renderSeparateSkateboard { true };
    
    // Player rendering data
    const int X_POS                   { 75 };
    const int Y_POS_DEFAULT           { 320 };
    float     textureRotation         { 0.0f };
    float     shadowRotation          { 0.0f };
    float     shadow2Rotation         { 0.0f };
    
    const int SPRITE_WIDTH            { 92 };
    const int SPRITE_HEIGHT           { 108 };
    const int SPRITE_HEIGHT_DUCK      { 65 };
    const int SKATEBOARD_HEIGHT       { 16 };
    
    const int BACK_HEAD_OFFSET        { 35 };
    const int FRONT_SKATEBOARD_OFFSET { 6 };
    const int BACK_SKATEBOARD_OFFSET  { 10 };
    const int SHADOW_OFFSET           { 30 };
    
    int       shadowUpdateCounter     { 0 };
    
    Graphics* graphics            { nullptr };
    SDL_Texture* renderTexture    { nullptr };
    SDL_Texture* playerStand      { nullptr };
    SDL_Texture* playerDuck       { nullptr };
    Mix_Chunk* kickoff            { nullptr };
    Mix_Chunk* playerLand1        { nullptr };
    Mix_Chunk* playerLand2        { nullptr };
    Mix_Chunk* highJump           { nullptr };
    Mix_Chunk* highJumpLand       { nullptr };
    Mix_Chunk* duckSound          { nullptr };
    Mix_Chunk* deathSound         { nullptr };
    Mix_Chunk* levelUp            { nullptr };
    
    
    SDL_Rect playerPos     { X_POS, Y_POS_DEFAULT, SPRITE_WIDTH, SPRITE_HEIGHT - SKATEBOARD_HEIGHT};
    SDL_Rect playerClip    { 0, 0, SPRITE_WIDTH, SPRITE_HEIGHT - SKATEBOARD_HEIGHT };                // only player
    SDL_Rect skateBoardClip{ 0, SPRITE_HEIGHT - SKATEBOARD_HEIGHT, SPRITE_WIDTH, SKATEBOARD_HEIGHT}; // only skateboard
    SDL_Rect skateBoardPos { X_POS, Y_POS_DEFAULT + SPRITE_HEIGHT - SKATEBOARD_HEIGHT, SPRITE_WIDTH, SKATEBOARD_HEIGHT };
    
    SDL_Rect playerShadowPos   = playerPos ;
    SDL_Rect playerShadowClip = playerClip;
    SDL_Rect skateBoardShadowPos = skateBoardPos;
    SDL_Rect playerShadow2Pos   = playerPos ;
    SDL_Rect playerShadow2Clip = playerClip;
    SDL_Rect skateBoardShadow2Pos = skateBoardPos;
};

#endif