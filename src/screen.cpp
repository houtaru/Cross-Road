#include "screen.hpp"
#include "constants.hpp"
#include "screenMain.hpp"
#include "screenPlay.hpp"
#include "screenScore.hpp"
#include "screenPause.hpp"
#include "screenSetting.hpp"

#include <iostream>

using namespace std;

shared_ptr<View> Screen::view = View::GetInstance();
shared_ptr<Sound> Screen::sound = Sound::GetInstance();

const SDL_Rect Screen::RECT_BACKGROUND = {
    0, 0,
    Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT
};

Screen::Screen():
    background(),
    screenType(),
    nextScreenType()
{
    //cerr << "Constructing Screen...\n";
}

Screen::~Screen() {
    //cerr << "Destructing Screen...\n";
}

shared_ptr<Screen> Screen::CreateScreenFromScreenType(ScreenType screenType) {
    switch (screenType) {
        case MAIN:
            return shared_ptr<Screen>((Screen*) new ScreenMain());
            break;
        case PLAY:
            return shared_ptr<Screen>((Screen*) new ScreenPlay());
            break;
        case LOAD:
            return shared_ptr<Screen>((Screen*) new ScreenPlay(false));
            break;
        case HIGHSCORE:
            return shared_ptr<Screen>((Screen*) new ScreenScore());
            break;
        case PAUSE:
            return shared_ptr<Screen>((Screen*) new ScreenPause());
            break;
        case SETTING:
            return shared_ptr<Screen>((Screen*) new ScreenSetting());
            break;
        default:
            throw "No such Screen!\n";
    }
    return NULL;
}

void Screen::AddButton(shared_ptr<Texture> buttonView, function<void()> OnMouseClick) {
    buttons.push_back(Button(buttonView, OnMouseClick));
    buttonStates.push_back(false);
}

void Screen::SetButtonDefault(shared_ptr<Texture> buttonView, function<void()> OnMouseClick) {
    buttonDefault = Button(buttonView, OnMouseClick);
    buttonDefaultState = false;
}

void Screen::ClearButton() {
    buttons.clear();
    buttonStates.clear();
    buttonDefault = Button();
    buttonDefaultState = false;
}

void Screen::Start() {
}

void Screen::Redraw() {}

ScreenType Screen::Loop(SDL_Event &event) {
    if (event.type == SDL_MOUSEMOTION) {
        HandleMouse(
            [this](Button button) {
                if (button.obj == nullptr) {
                    Redraw();
                } else {
                    view->RenderTexture(background);
                    view->RenderTexture(button.obj);
                }
            },
            [](__attribute__((unused)) Button button) {}
        );
    } else if (event.type == SDL_MOUSEBUTTONUP) {
        HandleMouse(
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

void Screen::Save() {}

ScreenType Screen::GetType() {
    return screenType;
}

bool Screen::IsMouseOverRect(const SDL_Rect &rect) {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    return (
        rect.x <= mouseX &&
        mouseX <= rect.x + rect.w &&
        rect.y <= mouseY &&
        mouseY <= rect.y + rect.h
    );
}

void Screen::HandleMouse(function<void(Button button)> CallbackRender, function<void(Button button)> CallbackClick) {
    bool anyInside = false;
    for (size_t i = 0; i < buttons.size(); ++i) {
        auto button = buttons[i];
        if (IsMouseOverRect(button.obj->rect)) {
            anyInside = true;
            buttonDefaultState = false;
            CallbackClick(button);
            if (!buttonStates[i]) {
                buttonStates[i] = true;
                CallbackRender(button);
            }
        } else {
            buttonStates[i] = false;
        }
    }
    if (!anyInside) {
        CallbackClick(buttonDefault);
        if (!buttonDefaultState) {
            buttonDefaultState = true;
            CallbackRender(buttonDefault);
        }
    }
}
