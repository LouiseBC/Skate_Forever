#include "GameState_Menu.hpp"
#include "GameState_Main.hpp"

bool MenuState::init(Graphics *graph, Game *gam) {
    graphics = graph;
    game = gam;
    
    backgroundTex = graphics->loadTexture("Assets/menubackground.png");
    arrow = graphics->loadTexture("Assets/arrow.png");
    startButton.isActive = true;
    
    move = graphics->loadSound("Assets/menu_move.wav");
    select = graphics->loadSound("Assets/menu_select.wav");
    quitsound = graphics->loadSound("Assets/menu_quit.wav");
    
    startButton.texture = graphics->renderText("Start", "Assets/GreenFlame.ttf", fontColour, 30);
    quitButton.texture = graphics->renderText("Quit", "Assets/GreenFlame.ttf", fontColour, 30);
    
    loadPositions();
    
    return true;
}

MenuState::~MenuState() {
    Mix_FreeChunk(move);
    Mix_FreeChunk(select);
    Mix_FreeChunk(quitsound);
    
    backgroundTex = nullptr;
    arrow = nullptr;
    startButton.texture = nullptr;
    quitButton.texture = nullptr;
    
    graphics = nullptr;
    game = nullptr;
}

void MenuState::loadPositions(){
    int W; int H;
    // Menu button positions
    SDL_QueryTexture(startButton.texture, NULL, NULL, &W, &H);
    startButton.position = (SDL_Rect{WINDOW_WIDTH/2 - W/2, WINDOW_HEIGHT/2, W, H});
    
    SDL_QueryTexture(quitButton.texture, NULL, NULL, &W, &H);
    quitButton.position = (SDL_Rect{WINDOW_WIDTH/2 - W/2, startButton.position.y + 2*startButton.position.h, W, H});
    
    // Set selection arrow positions
    wrapButton(buttonType::start, arrow1Pos, arrow2Pos);
}

void MenuState::wrapButton(const int& button, SDL_Rect& arrow1, SDL_Rect& arrow2) {
    MenuButton activeButton;
    switch(button) {
        case buttonType::start: activeButton = startButton;
            break;
        case buttonType::quit: activeButton = quitButton;
            break;
    }
    
    int W; int H;
    SDL_QueryTexture(arrow, NULL, NULL, &W, &H);
    arrow1Pos = (SDL_Rect{activeButton.position.x - 2*W, activeButton.position.y + activeButton.position.h/2 - H/2, W, H});
    arrow2Pos = (SDL_Rect{activeButton.position.x + activeButton.position.w + W/2, activeButton.position.y
                + activeButton.position.h/2 - H/2, W, H});
}

void MenuState::handleEvents(SDL_Event &event) {
    if (event.type == SDL_QUIT)
        game->setQuit();
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_ESCAPE)
            game->setQuit();
        
        if (event.key.keysym.sym == SDLK_DOWN) {
            if (startButton.isActive) {
                wrapButton(buttonType::quit, arrow1Pos, arrow2Pos);
                quitButton.isActive = true;
                startButton.isActive = false;
                Mix_PlayChannel(-1, move, 0);
            }
        }
        if (event.key.keysym.sym == SDLK_UP) {
            if (quitButton.isActive) {
                wrapButton(buttonType::start, arrow1Pos, arrow2Pos);
                startButton.isActive = true;
                quitButton.isActive = false;
                Mix_PlayChannel(-1, move, 0);
            }
        }
        if (event.key.keysym.sym == SDLK_RETURN) {
            if (startButton.isActive) {
                Mix_PlayChannel(-1, select, 0);
                SDL_Delay(400);
                game->pushState(new MainGameState);
            }
            else if (quitButton.isActive == true) {
                Mix_PlayChannel(-1, quitsound, 0);
                SDL_Delay(200);
                game->setQuit();
            }
        }
    }
}

void MenuState::update(const float &deltaTime) {
    if (startButton.isActive) {
        setRollover(0);
        jiggleButton(startButton, deltaTime);
    }
    else if (quitButton.isActive) {
        setRollover(1);
        jiggleButton(quitButton, deltaTime);
    }
}

void MenuState::jiggleButton(MenuButton& activebutton, const float& deltaTime) {
    // Not implemented deltaTime - To Do.
    // Move every 6 frames
    if (activebutton.animationCount / 6 == 1) {
        if (activebutton.positionChange == 2)
            activebutton.direction = -1; // move up
        else if (activebutton.positionChange == 0)
            activebutton.direction = 1; // move down
        
        activebutton.position.y += activebutton.direction;
        activebutton.positionChange += activebutton.direction;
        activebutton.animationCount = 0;
    }
    else
        ++activebutton.animationCount;
}

void MenuState::setRollover(const int& button) {
    switch(button) {
        case 0: quitButton.texture = graphics->renderText("Quit", "Assets/GreenFlame.ttf", fontColour, 30);
            startButton.texture = graphics->renderText("Start", "Assets/GreenFlame.ttf", rolloverColour, 30);
            break;
        case 1: startButton.texture = graphics->renderText("Start", "Assets/GreenFlame.ttf", fontColour, 30);
            quitButton.texture = graphics->renderText("Quit", "Assets/GreenFlame.ttf", rolloverColour, 30);
            break;
    }
}

void MenuState::render() {
    graphics->renderClear();
    
    graphics->renderTexture(backgroundTex, &backgroundPos);
    graphics->renderTexture(startButton.texture, &startButton.position);
    graphics->renderTexture(quitButton.texture, &quitButton.position);
    graphics->renderTexture(arrow, &arrow1Pos);
    graphics->renderRotatedTexture(arrow, &arrow2Pos, 0, NULL, SDL_FLIP_HORIZONTAL);
    
    graphics->renderPresent();
}