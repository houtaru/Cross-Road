#include "player.hpp"
#include "constants.hpp"

using namespace std;

Player::Player() : Object() { velocity[0] = 4; }
Player::Player(string path, SDL_Rect rect, bool _flip) : Object(path, rect, _flip) { velocity[0] = 4; }
Player::~Player() {}

void Player::setVel(SDL_Event &event) {
     //  If a key was pressed or release
    if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
        switch (event.key.keysym.sym) {
            case SDLK_UP: velY -= velocity[0]; break;
            case SDLK_DOWN: velY += velocity[0]; break;
            case SDLK_LEFT: velX -= velocity[0]; break;
            case SDLK_RIGHT: velX += velocity[0]; break;
        }
    } else if (event.type == SDL_KEYUP && event.key.repeat == 0) {
        if (velX != 0 || velY != 0) {
            switch (event.key.keysym.sym) {
                case SDLK_UP: velY += velocity[0]; break;
                case SDLK_DOWN: velY -= velocity[0]; break;
                case SDLK_LEFT: velX += velocity[0]; break;
                case SDLK_RIGHT: velX -= velocity[0]; break;
            }
        }
    }
}

bool Player::canMove(std::vector<std::vector<shared_ptr<Object>>> &stuff) {
    //  Move the player left or right
    obj->rect.x += velX;
    x = obj->rect.x;
    //  If the player went too far left or right 
    if ((obj->rect.x < 0) || (obj->rect.x + obj->rect.w > Constants::SCREEN_WIDTH)) obj->rect.x -= velX;
    //  If the player overlapped stuff
    for (int i = 0; i < stuff.size(); ++i) {
        for (int j = 0; j < stuff[i].size(); ++j)
            if (isCollision(stuff[i][j])) {
                obj->rect.x -= velX;
            }
    }

    //  Move the player up or down
    obj->rect.y += velY;
    y = obj->rect.y + (obj->rect.h - Constants::OBJECT_HEIGHT);
    //  If the player went too far up or down
    if ((obj->rect.y < 0) || (obj->rect.y + obj->rect.h > Constants::SCREEN_HEIGHT)) obj->rect.y -= velY;
    //  If the player overlapped stuff
    for (int i = 0; i < stuff.size(); ++i) {
        for (int j = 0; j < stuff[i].size(); ++j)
            if (isCollision(stuff[i][j])) {
                obj->rect.y -= velY;
            }
    }

    return true;
}