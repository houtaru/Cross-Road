#pragma once

#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

namespace Pointer {
    std::shared_ptr<SDL_Window> createSdlWindow(SDL_Window *p);
    std::shared_ptr<SDL_Surface> createSdlSurface(SDL_Surface *p);
    std::shared_ptr<SDL_Renderer> createSdlRenderer(SDL_Renderer *p);
    std::shared_ptr<SDL_Texture> createSdlTexture(SDL_Texture *p);

    std::shared_ptr<TTF_Font> createTtfFont(TTF_Font *p);
}