#include "engine.hpp"
#include <iostream>

Engine::Engine() {}
Engine::~Engine() {}

void Engine::init(const char* title, int xp, int yp, int w, int h, bool fullscreen) {
    int flags = 0;
    width = w;
    height = h;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        win = SDL_CreateWindow(title, xp, yp, w, h, flags);
        ren = SDL_CreateRenderer(win, -1, 0);
        map = new LevelMap();
        player = new Player();
        if (ren) {
            SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        }
        map->addWall(200.0, 100.0, 600.0, 100.0, 255, 0, 0);
        map->addWall(600.0, 100.0, 600.0, 300.0, 255, 255, 0);
        map->addWall(300.0, 200.0, 400.0, 300.0, 0, 255, 0);
        map->addWall(600.0, 300.0, 200.0, 300.0, 0, 255, 255);
        map->addWall(200.0, 300.0, 200.0, 100.0, 0, 0, 255);
        player->init(w/2, h/2, 0, 2); //initialise player 
        isRunning = true;
    }
    else {
        isRunning = false;
    }
}

void Engine::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYDOWN: //key events
            switch (event.key.keysym.sym)
            {
                case SDLK_w:
                    player->move(1, 0);
                    break;
                case SDLK_a:
                    player->move(0, 1);
                    break;
                case SDLK_s:
                    player->move(-1, 0);
                    break;
                case SDLK_d:
                    player->move(0, -1);
                    break;
                default:
                    break;
            }
        case SDL_MOUSEMOTION:
            int x, y;
            SDL_GetMouseState(&x, &y);
            if (x < 2) SDL_WarpMouseInWindow(win, width - 2, y);
            if (x > (width - 2)) SDL_WarpMouseInWindow(win, 2, y); //adjust mouse position if it leaves window bounds
            break;
        default:
            break;
    }
}

void Engine::update() {
    for (int i = -150; i < 150; i++)
    {
        double angle = player->getAngle() + (i / 150.0) * PI / 6;
        TextureInfo line = map->getWall(angle, player->getAngle(), player->getX(), player->getY()); // get wall in direction
        if (line.dist > 0) { //if line height is -1 then no wall is detected
            wall_heights[i+150] = line; 
        }
        else {
            wall_heights[i+150] = { -1.0 , 0, 0, 0 };
        }
    }
    int x;
    SDL_GetRelativeMouseState(&x, NULL);
    player->setAngle(player->getAngle() + (x / (float)width) * 2 * PI); //set player position according to mouse pos
}

void Engine::render() {
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);;
    SDL_RenderClear(ren);
    for (size_t i = 0; i < 300; i++)
    {
        if (wall_heights[i].dist > 0) {
            float dfc = (int)MIN(8000/wall_heights[i].dist, height / 2); //wall height
            float dfc_scaled = MIN(100 / wall_heights[i].dist, 1.0); //wall shade according to distance
            SDL_Rect r;
            r.w = 2;
            r.h = dfc * 2;
            r.x = i * 2;
            r.y = height / 2 - dfc;
            SDL_SetRenderDrawColor(ren, (int)(dfc_scaled * wall_heights[i].r), 
                                    (int)(dfc_scaled * wall_heights[i].g), 
                                    (int)(dfc_scaled * wall_heights[i].b), 
                                    255);
            SDL_RenderFillRect(ren, &r);
        }
    }
    SDL_RenderPresent(ren);
}

void Engine::clean() {
    SDL_DestroyWindow(win);
    SDL_DestroyRenderer(ren);
    delete map;
    delete player;
    map = NULL;
    player = NULL;
    SDL_Quit();
}