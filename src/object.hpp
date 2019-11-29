#pragma once
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

struct Object {
    std::string path;
    SDL_Rect rect;
    Object(std::string _path, const SDL_Rect &_rect): path(_path), rect(_rect) {}
};

struct RectObject {
    SDL_Rect rect;
    SDL_Color color;
    RectObject(const SDL_Rect &_rect, const SDL_Color &_color): rect(_rect), color(_color) {}
};

struct FontObject {
    std::string text;
    int fontSize;
    SDL_Rect rect;
    bool isBold;
    FontObject(std::string _text, const SDL_Rect &_rect): text(_text), fontSize(24), rect(_rect), isBold(false) {}
    FontObject(std::string _text, int _fontSize, const SDL_Rect &_rect):
        text(_text), fontSize(_fontSize), rect(_rect), isBold(false) {}
    FontObject(std::string _text, int _fontSize, const SDL_Rect &_rect, bool _isBold):
        text(_text), fontSize(_fontSize), rect(_rect), isBold(_isBold) {}
};