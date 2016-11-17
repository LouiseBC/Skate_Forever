#ifndef GameState_Menu_hpp
#define GameState_Menu_hpp
#include <SDL2_mixer/SDL_mixer.h>
#include "Gamestate.hpp"
#include "MenuButton.h"

class MenuState : public GameState{
public:
    bool init(Graphics* graphics, Game* game);
    ~MenuState();

    void handleEvents(SDL_Event& e);
    void update(const float& deltaTime);
    void render();
    
    void loadPositions();
    void wrapButton(const int& button, SDL_Rect& arrow1, SDL_Rect& arrow2);
    void wrapQuitButton(SDL_Rect& arrow1, SDL_Rect& arrow2);

    void setRollover(const int& mouseposition);
    void jiggleButton(MenuButton& activebutton, const float& deltaTime);
private:
    MenuButton* activeButton;
    MenuButton startButton;
    MenuButton scoresButton;
    MenuButton quitButton;
    enum buttonType { start = 0, quit };
    
    SDL_Colour fontColour { 225, 225, 225, 1 };
    SDL_Colour rolloverColour { 240, 197, 203, 1 };
    
    SDL_Texture* backgroundTex { nullptr };
    SDL_Rect     backgroundPos { 0, 0, 720, 480 };
    SDL_Texture* arrow         { nullptr };
    SDL_Rect     arrow1Pos;
    SDL_Rect     arrow2Pos;
    
    Mix_Chunk* move         { nullptr };
    Mix_Chunk* select       { nullptr };
    Mix_Chunk* quitsound    { nullptr };
    
    const int WINDOW_WIDTH  { 720 };
    const int WINDOW_HEIGHT { 480 };
    
    Graphics* graphics;
    Game* game;
};

#endif
