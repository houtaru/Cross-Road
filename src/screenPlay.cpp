#include "screenPlay.hpp"
#include "constants.hpp"
#include "pointer.hpp"

#include <iostream>

using namespace std;

ScreenPlay::ScreenPlay():
    newGame(true),
    level(1),
    eventMap({
        {SDLK_RIGHT, &ScreenPlay::handleButtonArrowRight},
        {SDLK_LEFT, &ScreenPlay::handleButtonArrowLeft},
        {SDLK_DOWN, &ScreenPlay::handleButtonArrowDown},
        {SDLK_UP, &ScreenPlay::handleButtonArrowUp},
        {SDLK_ESCAPE, &ScreenPlay::handleButtonEscape},
        {SDLK_SPACE, &ScreenPlay::handleButtonSpace},
        {SDLK_p, &ScreenPlay::handleButtonP}
    })
{
    background = make_shared<Texture>(
        "assets/images/ground/ground_01.png",
        RECT_BACKGROUND
    );
    cerr << "Constructing Screen Play....\n";
}

ScreenPlay::~ScreenPlay() {
    cerr << "Destructing Screen Play...\n";
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
    if (event.type == SDL_KEYDOWN) {
        int eventKey = event.key.keysym.sym;
        auto it = eventMap.find(eventKey);
        if (it != eventMap.end()) {
            FunctionPointer fp = it->second;
            (this->*fp)();
        }
    }
    //updateViewGround();
    return nextScreenType;
}

void ScreenPlay::updateViewGround() {
    //controller->updateObstacle(level);

    view->renderTexture(background);
    view->renderTexture(controller->getObstacles());
    view->renderTexture(controller->getStuff());
    view->renderPresent();
}

void ScreenPlay::handleButtonArrowUp() {
    controller->moveUp();
    // updateViewGround();
}

void ScreenPlay::handleButtonArrowDown() {
    controller->moveDown();
    // updateViewGround();
}

void ScreenPlay::handleButtonArrowLeft() {
    controller->moveLeft();
    // updateViewGround();
}

void ScreenPlay::handleButtonArrowRight() {
    controller->moveRight();
    // updateViewGround();
}

void ScreenPlay::handleButtonEscape() {
    
}

void ScreenPlay::handleButtonSpace() {
    nextScreenType = BACK_TO_PREV;
}

void ScreenPlay::handleButtonP() {

}
