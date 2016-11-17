#ifndef GameState_Main_hpp
#define GameState_Main_hpp
#include "GameState.hpp"
#include "Player.hpp"
#include "Scenery.hpp"
#include "Obstacles.hpp"

class MainGameState : public GameState {
public:
    bool init(Graphics* graphics, Game* game);
    ~MainGameState();
    
    void handleEvents(SDL_Event& e);
    void update(const float& deltaTime);
    void render();
    void renderScore();
    void renderHighScore();
    void renderCountDown(const std::string message1, const std::string message2, const std::string message3);
    void renderPause(const std::string& message);
    
    void getHighScore();
    void updateHighScore();
    void setGameDifficulty(int playerscore);
private:
    bool  pause          { false };
    bool  gameBeginning  { true };
    float gameSpeed      { 1.2f };
    int   playerScore    { -1 };
    int   highScore;
    float countDownPacer { 0 };
    std::string countDown { "" };
    
    Game* game         { nullptr };
    Graphics* graphics { nullptr };
    
    Player player;
    Scenery scenery;
    Obstacles obstacles;
    
    Mix_Music* music { nullptr };
    Mix_Chunk* pauseStart { nullptr };
    Mix_Chunk* pauseStop  { nullptr };
    
    // Score rendering
    SDL_Texture* scoreTexture { nullptr };
    SDL_Texture* highScoreTexture { nullptr };
    SDL_Texture* countDownTexture { nullptr };
    SDL_Texture* pauseTexture     { nullptr };
    
    const int WINDOW_WIDTH  { 720 };
    const int WINDOW_HEIGHT { 480 };
};

#endif