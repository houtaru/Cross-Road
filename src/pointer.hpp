#pragma once

#include <memory>

#ifdef __APPLE__
    #include <SDL.h>
    #include <SDL_image.h>
    #include <SDL_ttf.h>
    #include <SDL_mixer.h>
#else
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
    #include <SDL2/SDL_ttf.h>
    #include <SDL2/SDL_mixer.h>
#endif

// Wrap SDL pointer into shared_ptr for safer destruction
namespace Pointer {
    // Wrap SDL_Window* into shared_ptr 
    //
    // Example:
    //    createSdlWindow(SDL_CreateWindow(const char* title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, int width, int height, SDL_WINDOW_SHOWN))
    //
    std::shared_ptr<SDL_Window> CreateSdlWindow(SDL_Window *p);

    // Wrap SDL_Surface* into shared_ptr 
    //
    // Example:
    //    createSdlSurface(IMG_Load(const char* path)
    //    createSdlSurface(SDL_GetWindowSurface(SDL_Window *window))
    //
    std::shared_ptr<SDL_Surface> CreateSdlSurface(SDL_Surface *p);
    
    // Wrap SDL_Renderer* into shared_ptr 
    //
    // Example:
    //    createSdlRenderer(SDL_CreateRenderer(SDL_Window *window, -1, SDL_RENDERER_ACCELERATED))
    //
    std::shared_ptr<SDL_Renderer> CreateSdlRenderer(SDL_Renderer *p);

    // Wrap SDL_Texture* into shared_ptr 
    //
    // Example:
    //    createSdlTexture(SDL_CreateTextureFromSurface(SDL_Renderer *render, SDL_Surface *loadedSurface))
    //
    std::shared_ptr<SDL_Texture> CreateSdlTexture(SDL_Texture *p);

    // Wrap Mix_Music* into shared_ptr 
    //
    // Example:
    //    createMixMusic(Mix_LoadMUS(const char *path))
    //
    std::shared_ptr<Mix_Music> CreateMixMusic(Mix_Music *p);

    // Wrap Mix_Chunk* into shared_ptr 
    //
    // Example:
    //    createMixChunk(Mix_LoadWAV(const char *path))
    //
    std::shared_ptr<Mix_Chunk> CreateMixChunk(Mix_Chunk *p);

    // Wrap SDL_Surface* into shared_ptr 
    //
    // Example:
    //    creatteTtfFont(TTF_OpenFont(const char *path, int fontSize))
    //
    std::shared_ptr<TTF_Font> CreateTtfFont(TTF_Font *p);
}