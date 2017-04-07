#ifndef GameState_Main_hpp
#define GameState_Main_hpp
#include "GameState.hpp"
#include "Player.hpp"
#include "Scenery.hpp"
#include "Obstacles.hpp"
#include "HUD.hpp"

class HUD;

class MainGameState : public GameState {
public:
    bool init(Graphics* graphics, Game* game);
    ~MainGameState();
    
    void handleEvents(SDL_Event& e);
    void update(const float& deltaTime);
    void render();
    void restart();

    void getHighScore();
    void updateHighScore();
    void setGameDifficulty(int playerscore);
private:
    bool  paused              { false };
    bool  isGameBeginning      { true };
    float countDownTimer     { 0.0f };
    bool  playerIsDead       { false };
    int   playerScore        { -1 };
    int   highScore;
    const float defaultSpeed { 1.6f };
    float gameSpeed          { defaultSpeed };
    
    Game* game         { nullptr };
    Graphics* graphics { nullptr };
    
    Player player;
    Scenery scenery;
    Obstacles obstacles;
    HUD hud;
    
    Mix_Music* music { nullptr };
    Mix_Chunk* pauseStart { nullptr };
    Mix_Chunk* pauseStop  { nullptr };
};

#endif