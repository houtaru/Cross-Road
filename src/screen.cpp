#include "screen.hpp"
#include "constants.hpp"
#include "screenMain.hpp"
#include "screenPlay.hpp"

#include <iostream>

using namespace std;

shared_ptr<View> Screen::view = View::getInstance();
shared_ptr<Sound> Screen::sound = Sound::getInstance();
shared_ptr<Controller> Screen::controller = Controller::getInstance();

const SDL_Rect Screen::RECT_BACKGROUND = {
    0, 0,
    Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT
};

Screen::Screen():
    background(),
    screenType(),
    nextScreenType()
{
    cerr << "Constructing Screen...\n";
}

Screen::~Screen() {
    cerr << "Destructing Screen...\n";
}

shared_ptr<Screen> Screen::createScreenFromScreenType(ScreenType screenType) {
    switch (screenType) {
        case MAIN:
            return shared_ptr<Screen>((Screen*) new ScreenMain());
            break;
        case PLAY:
            return shared_ptr<Screen>((Screen*) new ScreenPlay());
            break;
        case PAUSE:
            // return shared_ptr<Screen>((Screen*) new PauseScreen());
            break;
        case INSTRUCTION:
            // return shared_ptr<Screen>((Screen*) new InstructionScreen());
            break;
        case BEFORE_END:
            // return shared_ptr<Screen>((Screen*) new BeforeEndScreen());
            break;
        case ENDGAME:
            // return shared_ptr<Screen>((Screen*) new EndgameScreen());
            break;
        default:
            throw "No such Screen!\n";
    }
    return NULL;
}

void Screen::addButton(shared_ptr<Texture> buttonView, function<void()> onMouseClick) {
    buttons.push_back(Button(buttonView, onMouseClick));
    buttonStates.push_back(false);
}

void Screen::setButtonDefault(shared_ptr<Texture> buttonView, function<void()> onMouseClick) {
    buttonDefault = Button(buttonView, onMouseClick);
    buttonDefaultState = false;
}

void Screen::clearButton() {
    buttons.clear();
    buttonStates.clear();
    buttonDefault = Button();
    buttonDefaultState = false;
}

void Screen::start() {
}

void Screen::redraw() {
}

ScreenType Screen::loop(SDL_Event &event) {
    if (event.type == SDL_MOUSEMOTION) {
        handleMouse(
            [this](Button button) {
                if (button.obj == nullptr) {
                    redraw();
                } else {
                    view->renderTexture(background);
                    view->renderTexture(button.obj);
                }
            },
            [](__attribute__((unused)) Button button) {}
        );
    } else if (event.type == SDL_MOUSEBUTTONUP) {
        handleMouse(
            [](__attribute__((unused)) Button button) {},
            [this](Button button) {
                if (button.callback != nullptr) {
                    button.callback();
                }
            }
        );
    }
    return nextScreenType;
}

ScreenType Screen::getType() {
    return screenType;
}

bool Screen::isMouseOverRect(const SDL_Rect &rect) {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    return (
        rect.x <= mouseX &&
        mouseX <= rect.x + rect.w &&
        rect.y <= mouseY &&
        mouseY <= rect.y + rect.h
    );
}

void Screen::handleMouse(function<void(Button button)> callbackRender, function<void(Button button)> callbackClick) {
    bool anyInside = false;
    for (size_t i = 0; i < buttons.size(); ++i) {
        auto button = buttons[i];
        if (isMouseOverRect(button.obj->rect)) {
            anyInside = true;
            buttonDefaultState = false;
            callbackClick(button);
            if (!buttonStates[i]) {
                buttonStates[i] = true;
                callbackRender(button);
            }
        } else {
            buttonStates[i] = false;
        }
    }
    if (!anyInside) {
        callbackClick(buttonDefault);
        if (!buttonDefaultState) {
            buttonDefaultState = true;
            callbackRender(buttonDefault);
        }
    }
}