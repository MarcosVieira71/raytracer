#include "WindowSDL.h"

#include "PixelBuffer.h"
WindowSDL::WindowSDL (int w, int h) : width(w), height(h)
{
    SDL_Init(SDL_INIT_VIDEO);

    win = SDL_CreateWindow("Preview", w, h, 0);

    ren = SDL_CreateRenderer(win, nullptr);

    tex = SDL_CreateTexture(
        ren,
        SDL_PIXELFORMAT_RGB24,
        SDL_TEXTUREACCESS_STREAMING,
        w, h
    );
}

void WindowSDL::update(const PixelBuffer& buffer)
{
    SDL_UpdateTexture(tex, nullptr, buffer.data.data(), width * 3);
    SDL_RenderClear(ren);
    SDL_RenderTexture(ren, tex, nullptr, nullptr);
    SDL_RenderPresent(ren);
}

WindowSDL::~WindowSDL()
{
    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
