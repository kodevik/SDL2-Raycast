#ifndef engine_hpp
#define engine_hpp
#define PI 3.1415926535897
#define MIN(x, y) (!(x < y) ? y : x)
#define MAX(x, y) (!(x > y) ? y : x)

#include "SDL2/SDL.h"
#include "levelmap.hpp"
#include "player.hpp"

class Engine {
public:
    Engine();
    ~Engine();
    void init(const char* title, int xp, int yp, int w, int h, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void clean();
    bool running() { return isRunning; }
private:
    bool isRunning;
    int rotation = 0;
    int width;
    int height;
    SDL_Window *win;
    SDL_Renderer *ren;
    LevelMap *map = nullptr;
    Player *player = nullptr;
    TextureInfo wall_heights[200];
};

#endif