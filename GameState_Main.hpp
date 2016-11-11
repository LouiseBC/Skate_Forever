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
    
    void setGameDifficulty(int playerscore);
    
private:
    bool   pause       { false };
    float  gameSpeed   { 1.0f };
    bool   gamestart   { false };
    
    Game* game         { nullptr };
    Graphics* graphics { nullptr };
    
    Player player;
    Scenery scenery;
    Obstacles obstacles;
};

#endif