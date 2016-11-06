#include "Game.hpp"
#include "Gamestate.hpp"

Game::Game() {
    quit = false;
}

bool Game::init(GameState *state) {
    graphics.setup();
    pushState(state);
    return true;
}

void Game::pushState(GameState *state) {
    states.push_back(state);
    if (state->init(&graphics, this) == false)
        quit = true;
}

void Game::loop()
{
    while(quit == false)
    {
        update();
        render();
    }
    quitGame();
}

void Game::update()
{
        if(states.size() > 0){
            while(SDL_PollEvent(&event))
                states.back()->handleEvents(event);
        }
        
        if (states.size() > 0){
            oldTime = currentTime;
            currentTime = SDL_GetTicks();
            float deltatime = (float)(currentTime - oldTime) / 1000.0f;
            states.back()->update(deltatime);
        }
}

void Game::render()
{
    if(states.size() > 0)
        states.back()->render();
}

void Game::quitGame() {
    while(states.size() > 0)
    {
        delete states.back();
        states.pop_back();
    }
    graphics.destroy();
    SDL_Quit();
}

void Game::popState() {
    delete states.back();
    states.pop_back();
    
    if(states.size() == 0)
        quit = true;
}

void Game::setQuit() {
    quit = true;
}