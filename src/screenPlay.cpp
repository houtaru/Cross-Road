#include "screenPlay.hpp"
#include "constants.hpp"
#include "pointer.hpp"

#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

ScreenPlay::ScreenPlay():
    newGame(true),
    level(1)
{
    background = make_shared<Texture>(
        "assets/images/ground/ground_01.png",
        RECT_BACKGROUND
    );
    controller = make_shared<Controller>(level);
    //cerr << "Constructing Screen Play....\n";
}

ScreenPlay::~ScreenPlay() {
    //cerr << "Destructing Screen Play...\n";
}

void ScreenPlay::start() {
    screenType = nextScreenType = PLAY;
    view->renderTexture(background);
}

void ScreenPlay::redraw() {
    updateViewGround();
}

ScreenType ScreenPlay::loop(SDL_Event &event) {
    if (screenType != nextScreenType) {
        return nextScreenType;
    }

    if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
        //  If player finishes the current level
        if (controller->handlePlayer(event)) {
            ++level;
            //  Game just has 5 levels. If complete all of them, CONGRATULATION, YOU WIN
            if (level > 5) {
                cerr << "You win!\n";
                return BACK_TO_PREV;
            }
            //  Reset controller for new level
            controller = make_shared<Controller>(level);
            //  Start again
            start();
        }
    }

    if (controller->checkCollision()) {
        nextScreenType = BACK_TO_PREV;
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
    return nextScreenType;
}

void ScreenPlay::updateViewGround() {
    controller->updateObstacle(level);

    view->renderTexture(background);
    view->renderTexture(controller->getObstacles());
    view->renderTexture(controller->getStuff());
    view->renderTexture(controller->getPlayer());
}
