#include "engine.hpp"

Engine *eng = nullptr;

int main(int argc, char *argv[]) {
    Uint32 frameStart;
    int frameTime;
    eng = new Engine();
    eng->init("raycast", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, 0);
    while (eng->running()) { //main loop
        eng->handleEvents();
        eng->update();
        eng->render();
    }
    eng->clean();
    return 0;
}