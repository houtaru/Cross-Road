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
// 
//  @param
//  stuff: Vector of stuffs to not overlap
bool Player::Move(std::vector<std::vector<Object*>> &stuff) {
    //  Move the player left or right
    x += velX;
    box.x = x;
    //  If the player went too far left or right 
    if ((x < 0) || (x+w > SCREEN_WIDTH)) x -= velX;
    //  If the player overlapped stuff
    for (int i = 0; i < stuff.size(); ++i) {
        for (int j = 0; j < stuff[i].size(); ++j)
            if (CheckCollision(stuff[i][j])) {
                x -= velX;
            }
    }

    //  Move the player up or down
    y += velY;
    box.y = y + (h - ROCK_HEIGHT);
    //  If the player went too far up or down
    if ((y < 0) || (y+h > SCREEN_HEIGHT)) y -= velY;
    //  If the player overlapped stuff
    for (int i = 0; i < stuff.size(); ++i) {
        for (int j = 0; j < stuff[i].size(); ++j)
            if (CheckCollision(stuff[i][j])) {
                y -= velY;
            }
    }

    return true;
}
