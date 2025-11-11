#pragma once

#include <SDL3/SDL.h>

class PixelBuffer;

class WindowSDL
{
public:
    SDL_Window* win;
    SDL_Renderer* ren;
    SDL_Texture* tex;
    int width, height;

    WindowSDL(int w, int h);

    void update(const PixelBuffer& buffer);

    ~WindowSDL();

};
