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
    box.x = x;
    box.y = y;
    box.w = w;
    box.h = h;
} 
Object::~Object() {}

//  @brief
//  Move the object
void Object::Move() {
    if (x <= 0 - w) x = SCREEN_WIDTH;
    else {
        x -= 7;
        box.x = x;
    }
}

//  @brief
//  Render the object
void Object::Render() { 
    box.w = w;
    box.h = h;
    Texture::Render(x, y);
}

SDL_Rect Object::GetBox() const { return box; }