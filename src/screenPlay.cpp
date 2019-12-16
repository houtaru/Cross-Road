#include "screenPlay.hpp"
#include "constants.hpp"
#include "pointer.hpp"

#include <iostream>

using namespace std;

ScreenPlay::ScreenPlay():
    newGame(true),
    level(1)
{
    background = make_shared<Texture>(
        "assets/images/ground/ground_01.png",
        RECT_BACKGROUND
    );
    //cerr << "Constructing Screen Play....\n";
}

ScreenPlay::~ScreenPlay() {
    //cerr << "Destructing Screen Play...\n";
}

void ScreenPlay::start() {
    screenType = nextScreenType = PLAY;
    view->renderTexture(background);
    // view->renderPresent();
}

void ScreenPlay::redraw() {
    updateViewGround();
}

ScreenType ScreenPlay::loop(SDL_Event &event) {
    if (screenType != nextScreenType) {
        return nextScreenType;
    }
    if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
        controller->handlePlayer(event);
    }
    //updateViewGround();
    return nextScreenType;
}

void ScreenPlay::updateViewGround() {
    controller->updateObstacle(level);

    view->renderTexture(background);
    view->renderTexture(controller->getObstacles());
    view->renderTexture(controller->getStuff());
    view->renderTexture(controller->getPlayer());
    view->renderPresent();
}
