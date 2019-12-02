#include "player.hpp"

Player::Player() : Object() { velX = velY = 0; }
Player::Player(SDL_Renderer *&ren, int xSub, int ySub) : Object(ren, xSub, ySub) { velX = velY = 0; }
Player::~Player() {}

//  @brief
//  Set velocity according to the key player pressed
//
//  @param
//  e: Event from player
void Player::SetVel(SDL_Event &e) {
    //  If a key was pressed
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_UP: velY -= VELOCITY; break;
            case SDLK_DOWN: velY += VELOCITY; break;
            case SDLK_LEFT: velX -= VELOCITY; break;
            case SDLK_RIGHT: velX += VELOCITY; break;
        }
    } 
    //  If a key was released
    else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_UP: velY += VELOCITY; break;
            case SDLK_DOWN: velY -= VELOCITY; break;
            case SDLK_LEFT: velX += VELOCITY; break;
            case SDLK_RIGHT: velX -= VELOCITY; break;
        }
    }
}

//  @brief
//  Move the player
bool Player::Move() {
    //  Move the player left or right
    x += velX;
    box.x = x;
    //  If the player went too far left or right 
    if ((x < 0) || (x+w > SCREEN_WIDTH)) x -= velX;

    //  Move the player up or down
    y += velY;
    box.y = y;
    //  If the player went too far up or down
    if ((y < 0) || (y+h > SCREEN_HEIGHT)) y -= velY;

    return true;
}

//  @brief
//  Check whether player collide object or not
//
//  @param:
//  other: Other object on screen
bool Player::CheckCollision(Object *&other) {
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
    if(bottomA <= topB+9) return false;
    if(topA >= bottomB-9) return false;
    if(rightA <= leftB+7) return false;
    if(leftA >= rightB-7) return false;

    //  If none of the sides from A are outside B
    return true;
}