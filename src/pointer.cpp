#include "pointer.hpp"
#include <iostream>

using namespace std;

shared_ptr<SDL_Window> Pointer::createSdlWindow(SDL_Window *p) {
    shared_ptr<SDL_Window> res(p, [](SDL_Window *p) {
        if (p != nullptr) 
            SDL_DestroyWindow(p);
        p = nullptr;
        cerr << "Destroy temporary window done!\n";
    });
    return res;
}

shared_ptr<SDL_Surface> Pointer::createSdlSurface(SDL_Surface *p) {
    shared_ptr<SDL_Surface> res(p, [](SDL_Surface *p) {
        if (p != nullptr)  
            SDL_FreeSurface(p);
        p = nullptr;
        cerr << "Free temporary surface done!\n";
    });
    return res;
}

shared_ptr<SDL_Renderer> Pointer::createSdlRenderer(SDL_Renderer *p) {
    shared_ptr<SDL_Renderer> res(p, [](SDL_Renderer *p) {
        if (p != nullptr) 
            SDL_DestroyRenderer(p);
        p = nullptr;
        cerr << "Destroy temporary renderer done!\n";
    });
    return res;
}

shared_ptr<SDL_Texture> Pointer::createSdlTexture(SDL_Texture *p) {
    shared_ptr<SDL_Texture> res(p, [](SDL_Texture *p) {
        if (p != nullptr) 
            SDL_DestroyTexture(p);
        p = nullptr;
        cerr << "Destroy temporary texture done!\n";
    });
    return res;
}

std::shared_ptr<TTF_Font> Pointer::createTtfFont(TTF_Font *p) {
    shared_ptr<TTF_Font> res(p, [](TTF_Font *p) {
        if (p != nullptr)
            TTF_CloseFont(p);
        p = nullptr;
        cerr << "Close temporary font successfull!\n";
    });
    return res;
}