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
    void update(float deltaTime);
    void render();
private:
    Game* game         = nullptr;
    Graphics* graphics = nullptr;
    
    Player player;
    Scenery scenery;
    Obstacles obstacles;
};

#endif