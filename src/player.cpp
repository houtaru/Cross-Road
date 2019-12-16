#include "player.hpp"
#include "constants.hpp"

using namespace std;

Player::Player()
{
}

Player::~Player() {

}

bool Player::canMove(std::vector<std::vector<shared_ptr<Object>>> &stuff) {
    // //  Move the player left or right
    // x += velocity[0];
    // box.x = x;
    // //  If the player went too far left or right 
    // if ((x < 0) || (x/* + w*/ > Constants::SCREEN_WIDTH)) x -= velocity[0];
    // //  If the player overlapped stuff
    // for (int i = 0; i < stuff.size(); ++i) {
    //     for (int j = 0; j < stuff[i].size(); ++j)
    //         if (isCollision(stuff[i][j])) {
    //             x -= velocity[0];
    //         }
    // }

    // //  Move the player up or down
    // y += velocity[1];
    // box.y = y + (/*h -*/ Constants::ROCK_HEIGHT);
    // //  If the player went too far up or down
    // if ((y < 0) || (y /*+ h*/ > Constants::SCREEN_HEIGHT)) y -= velocity[1];
    // //  If the player overlapped stuff
    // for (int i = 0; i < stuff.size(); ++i) {
    //     for (int j = 0; j < stuff[i].size(); ++j)
    //         if (isCollision(stuff[i][j])) {
    //             y -= velocity[1];
    //         }
    // }

    // return true;
}