#ifndef Gamestate_hpp
#define Gamestate_hpp
#include "SDL2/SDL.h"
#include "Game.hpp"

class GameState {
public:
    virtual bool init(Graphics* graphics, Game* game)  = 0;
    virtual ~GameState() {};
    
    virtual void handleEvents(SDL_Event& event) = 0;
    virtual void update(const float& deltaTime) = 0;
    virtual void render() = 0;
};

#endif
