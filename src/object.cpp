#include "object.hpp"

Object::Object() : Texture() {
    x = y = 0;
    box.x = x;
    box.y = y;
    box.w = w;
    box.h = h;
} 
Object::Object(SDL_Renderer *&ren, int xSub, int ySub) : Texture(ren) {
    x = xSub;
    y = ySub;
    box.x = xSub;
    box.y = ySub;
    box.w = w;
    box.h = h;
} 
Object::~Object() {}

//  @brief
//  Move the object
//
//  @param
//  checkForward: True if forward lane and false if backward
//
//  @return
//  False if object goes further than 0 x-coordinate and true otherwise
bool Object::Move(bool checkForward) {
    if (
        (x <= 0 - w && checkForward) ||
        (x >= SCREEN_WIDTH + w && !checkForward)
    ) return false;
    else {
        x += (checkForward ? -7 : 7);
        box.x = x;
        return true;
    }
}

//  @brief
//  Render the object
void Object::Render(SDL_RendererFlip flip) { 
    box.w = w;
    box.h = h;
    Texture::Render(x, y, flip);
}

SDL_Rect Object::GetBox() const { return box; }
void Object::SetX(const int &a) { 
    x = a; 
    box.x = a;
    box.w = w;
    box.h = h;
}