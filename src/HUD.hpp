#ifndef HUD_hpp
#define HUD_hpp
#include <SDL2/SDL.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <string>

class Graphics;

class HUD {
public:
    void init(Graphics* graphs);
    void destroy();
    void restart();
    
    void renderScore(const int& score);
    void renderHighScore(const int& highscore);
    bool countDown(const float& timer, const std::string& message1, const std::string& message2, const std::string& message3);
    void renderCountDown(const std::string& message);
    
    void setBlendedRender();
    void unSetBlendedRender();
    
    void deathScreenOverlay();
    void fadeDeathScreenOverlay(const float& deltaTime);
    void renderDeathMsg(const std::string& message, const std::string& message2);
    void pauseScreenOverlay();
    void renderPauseMsg(const std::string& message);
    
private:
    Graphics* graphics;
    float counter { 0.5f};
    
    // Sounds
    Mix_Chunk*   countDownSound   { nullptr };
    Mix_Chunk*   goSound          { nullptr };
    int          soundsPlayed     { 0 };
    
    // Texture rendering
    SDL_Texture* scoreTexture     { nullptr };
    SDL_Texture* highScoreTexture { nullptr };
    SDL_Texture* countDownTexture { nullptr };
    SDL_Texture* pauseTexture     { nullptr };
    SDL_Texture* deathTexture     { nullptr };
    SDL_Texture* restartInstruction { nullptr };
    
    const int WINDOW_WIDTH  { 720 };
    const int WINDOW_HEIGHT { 480 };
    
    // Death/Pause screen overlay data
    SDL_Rect overlay { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
    float r { 255 }; float g { 255 }; float b { 255 };
};

#endif /* HUD_hpp */
