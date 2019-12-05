#include "object.hpp"
#include "player.hpp"

Object::Object() : Texture() {
    x = y = 0;
    box.x = x;
    box.y = y + (h - ROCK_HEIGHT);
    box.w = w;
    box.h = ROCK_HEIGHT;
} 
Object::Object(SDL_Renderer *&ren, int xSub, int ySub) : Texture(ren) {
    x = xSub;
    y = ySub;
    box.x = xSub;
    box.y = ySub + (h - ROCK_HEIGHT);
    box.w = w;
    box.h = ROCK_HEIGHT;
} 
Object::~Object() {}

//  @brief
//  Load texture from file
//
//  @param
//  renderer: The renderer of SDL
//  path: the local path to file
void Object::Load(std::string path) {
    Texture::Load(path);
    box.w = w;
    box.h = ROCK_HEIGHT;
    box.y = y + (h - ROCK_HEIGHT);
}

//  @brief
//  Polymorphism
void Object::SetVel(SDL_Event &e) {}

//  @brief
//  Polymorphism for player
//
//  @param
//  stuff: Vector of stuffs to not overlap
bool Object::Move(std::vector<std::vector<Object*>> &stuff) { return true; }

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
    Texture::Render(x, y, flip);
}

//  @brief
//  Check whether object collide other object or not
//
//  @param:
//  other: Other object on screen
bool Object::CheckCollision(Object *&other) {
    SDL_Rect otherBox = other->GetBox();

    //  The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //  Calculate the sides of rect A
    leftA = box.x;
    rightA = box.x + box.w;
    topA = box.y;
    bottomA = box.y + box.h;
        
    //  Calculate the sides of rect B
    leftB = otherBox.x;
    rightB = otherBox.x + otherBox.w;
    topB = otherBox.y;
    bottomB = otherBox.y + otherBox.h;

	//If any of the sides from A are outside of B
    if(bottomA <= topB) return false;
    if(topA >= bottomB) return false;
    if(rightA <= leftB) return false;
    if(leftA >= rightB) return false;

    //  If none of the sides from A are outside B
    return true;
}

SDL_Rect Object::GetBox() const { return box; }
void Object::SetX(const int &a) { x = a; box.x = a; }
void Object::SetY(const int &a) { y = a; box.y = a + (h - ROCK_HEIGHT); }
void Object::SetW(const int &a) { box.w = a; box.x = x + (w - box.w)/2; }