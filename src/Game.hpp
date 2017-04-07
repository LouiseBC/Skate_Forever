#ifndef Game_hpp
#define Game_hpp
#include "Graphics.hpp"
#include <vector>

class GameState;

class Game {
public:
    Game();
    
    bool init(GameState *state);
    void loop();
    
    void pushState(GameState *state);
    void popState();
    void setQuit();
private:
    void update();
    void render();
    void quitGame();
    
    bool quit    { false };
    std::vector<GameState*> states;
    
    Graphics graphics;
    SDL_Event event;
    
    Uint32 oldTime = 0;
    Uint32 currentTime = 0;
};

#endif
