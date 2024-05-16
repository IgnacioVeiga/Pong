#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include "FlowManager.h"

class Game
{
public:
    Game();
    ~Game();
    void run();
    static SDL_Renderer *renderer;
    static FlowManager *flowManager;

private:
    static SDL_Window *window;
};

#endif
