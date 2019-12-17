#include "controller.hpp"
#include "constants.hpp"
#include "player.hpp"

#include <iostream>
#include <glob.h>
#include <sstream>

using namespace std;

// Return an SDL_Rect from `path` which hash upper-left is (_x, _y)
//
SDL_Rect getRect(string path, int _x = 0, int _y = 0) {
    shared_ptr<SDL_Surface> tmp = Pointer::createSdlSurface(IMG_Load(path.c_str()));
    return SDL_Rect({
        _x, _y,
        tmp->w, tmp->h
    });
}

bool CheckOverlap(vector<shared_ptr<Object>> &lane, shared_ptr<Object> &newObject) {
    for (auto obj : lane) 
        if (obj != newObject && newObject->isCollision(obj)) return true;
    
    return false;
}

// Variables definitions
//
const vector<int> Controller::posY = {
    85, 145, 235, 295, 455, 515, 595, 655, 815+70, 60+875, 60+965,60+1025, 60+1185, 60+1245, 60+1325, 60+1385
};

const vector<pair<int, int>> Controller::posYcurb = {
    {0, 75}, 
    {355, 445}, 
    {715, Constants::SCREEN_HEIGHT}
};

Controller::Controller(int level)
{   
    srand(time(NULL));
    //cerr << "Constructing controller...\n";
    Glob(obstaclePath, "assets/images/obstacle/*");
    Glob(stuffPath, "assets/images/stuff/*");

    //  Initialize obstacles
    int index = 0;
    obstacles.resize(8);
    int maxObstacle = Constants::SCREEN_WIDTH / Constants::MAX_LENGHT_OBSTACLE;
    for (auto &lane : obstacles) {
        for (int i = 0; i < maxObstacle; ++i) {
            //  Random new type for new object
            int type = rand() % this->obstaclePath.size();
            shared_ptr<Object> temp(new Object(
                obstaclePath[type], getRect(obstaclePath[type], 0, posY[index]), (index % 4) > 1
            ));

            //  Random x-coordinate and check overlap with other objects' position
            do { 
                int pos = rand() % ((8 - level)*Constants::SCREEN_WIDTH/2);
                pos = ((index % 4) > 1 ? Constants::SCREEN_WIDTH - pos : pos);
                //  Set new position
                temp->setX(pos);
            } while (CheckOverlap(lane, temp));
            lane.push_back(temp); 
        }
        index++;
    }

    //  Initialize stuffs
    index = 0;
    stuff.resize(3);
    for (auto &curb : stuff) {
        int maxStuff;
        do {
            maxStuff = rand() % Constants::MAX_STUFF;
        } while (maxStuff < Constants::MIN_STUFF);

        for (int count = 0; count < maxStuff; ++count) {
            int type = rand() % this->stuffPath.size();
            shared_ptr<Object> temp(new Object(
                stuffPath[type], getRect(stuffPath[type])
            ));

            //  Random x-coordinate and check overlap with other objects' position
            do { 
                int posX = rand() % (Constants::SCREEN_WIDTH);
                if (posX > Constants::SCREEN_WIDTH - temp->getTexture()->rect.w) posX -= temp->getTexture()->rect.w;
                int posY = 0;
                do {
                    posY = rand() % posYcurb[index].second;
                    if (posY > posYcurb[index].second - temp->getTexture()->rect.h) posY -= temp->getTexture()->rect.h;
                } while (posY < posYcurb[index].first);

                //  Set new position
                temp->setX(posX);
                temp->setY(posY);
            } while (CheckOverlap(curb, temp));

            temp->setW(Constants::STUFF_WIDTH);
            temp->setH(Constants::ROCK_HEIGHT);
            curb.push_back(temp);
        }
        index++;
    }

    //  Initializer player
    string pathPlayer = "assets/images/player/player_01.png";
    player = make_shared<Player>(
        pathPlayer, getRect(pathPlayer, Constants::SCREEN_WIDTH/2, 0)
    );
    while (CheckOverlap(stuff[0], player)) {
        int posX = rand() % (Constants::SCREEN_WIDTH);
        if (posX > Constants::SCREEN_WIDTH - player->getTexture()->rect.x) posX -= player->getTexture()->rect.x;
        player->setX(posX);
    }
    player->setW(Constants::STUFF_WIDTH);

    //cerr << "Constructing controller done!\n";
}

Controller::~Controller() {
    //cerr << "Destructing controller...\n";
}

bool Controller::handlePlayer(SDL_Event &event) {
    while (SDL_PollEvent(&event) != 0)
        player->setVel(event);
    player->canMove(stuff);

    //  If player finishes the current level, return true
    if (player->getBox().y + player->getBox().h >= Constants::SCREEN_HEIGHT - 5) return true;
    return false;
}

void Controller::updateObstacle(int level) {
    int index = 0;
    for (auto &lane : obstacles) {
        for (int i = 0; i < (int) lane.size(); ++i) {
            if (!lane[i]->Move((index % 4) < 2)) {
                int type = rand() % this->obstaclePath.size();
                lane[i] = make_shared<Object>(
                    obstaclePath[type], getRect(obstaclePath[type], 0, posY[index]), (index % 4) > 1
                );
                do {
                    int pos = rand() % ((6 - level)*Constants::SCREEN_WIDTH/2);
                    pos = ((index % 4) > 1 ? -pos : pos + Constants::SCREEN_WIDTH);
                    lane[i]->setX(pos);
                } while (CheckOverlap(lane, lane[i]));
            }
        }
        index++;
    }
}

bool Controller::checkCollision() {
    for (auto &lane: obstacles) {
        for (int i = 0; i < (int) lane.size(); ++i) {
            if (player->isCollision(lane[i])) return true;
        }
    }
    return false;
}

std::vector<std::shared_ptr<Texture>> Controller::getObstacles() {
    std::vector<std::shared_ptr<Texture>> res;
    for (auto lane : obstacles)
        for (auto it : lane) res.push_back(it->getTexture());
    return res;
}

std::vector<std::shared_ptr<Texture>> Controller::getStuff() {
    std::vector<std::shared_ptr<Texture>> res;
    for (auto lane : stuff)
        for (auto it : lane) res.push_back(it->getTexture());
    return res;
}

std::shared_ptr<Texture> Controller::getPlayer() {
    return player->getTexture();
}
