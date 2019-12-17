#include "screenPause.hpp"

#include <iostream>

using namespace std;

const SDL_Rect ScreenPause::RECT_BACKGROUND_PAUSE {
    (Constants::SCREEN_WIDTH - 600) / 2, 
    (Constants::SCREEN_HEIGHT - 300) / 2, 
    600, 300
};

const SDL_Rect ScreenPause::RECT_TEXT_PAUSE {
    (Constants::SCREEN_WIDTH - 80 * 5) / 2,
    RECT_BACKGROUND_PAUSE.y + 50,
    400, 100
};

const SDL_Rect ScreenPause::RECT_BUTTON_PLAY = {
    Constants::SCREEN_WIDTH / 2 - 95,
    RECT_BACKGROUND_PAUSE.y + RECT_BACKGROUND_PAUSE.h - 143,
    72, 72
};

const SDL_Rect ScreenPause::RECT_BUTTON_SAVE = {
    Constants::SCREEN_WIDTH / 2 + 32,
    RECT_BACKGROUND_PAUSE.y + RECT_BACKGROUND_PAUSE.h - 140,
    66, 68
};

const SDL_Rect ScreenPause::RECT_BUTTON_EXIT = {
    RECT_BUTTON_SAVE.x + 120, 
    RECT_BUTTON_PLAY.y + 9,
    52, 66
};

const SDL_Rect ScreenPause::RECT_BUTTON_REPLAY = {
    RECT_BUTTON_PLAY.x - 110, 
    RECT_BUTTON_PLAY.y + 2,
    70, 70
};

ScreenPause::ScreenPause():
    buttonPlay(new Texture(
        "assets/images/button/button_play_pause.png",
        RECT_BUTTON_PLAY
    )),
    buttonExit(new Texture(
        "assets/images/button/button_exit_pause.png",
        RECT_BUTTON_EXIT
    )),
    buttonReplay(new Texture(
        "assets/images/button/button_replay_pause.png",
        RECT_BUTTON_REPLAY
    )),
    buttonSave(new Texture(
        "assets/images/button/button_save_pause.png",
        RECT_BUTTON_SAVE
    ))
{
    background = make_shared<Texture>(
        "assets/images/background/background_pause.png",
        RECT_BACKGROUND_PAUSE
    );
    //cerr << "Contructing Pause Screen done!\n";
}

ScreenPause::~ScreenPause() {
    //cerr << "Destructing Pause Screen done!\n";
}

void ScreenPause::Start() {
    //cerr << "  Start Pause Screen ...!\n";
    screenType = nextScreenType = PAUSE;

    //view->RenderClear();
    ClearButton();
    SetButtonDefault(background, nullptr);

    // play button
    function<void()> buttonPlayCallBack = bind(
        &ScreenPause::OnClickButtonPlay,
        this
    );
    AddButton(buttonPlay, buttonPlayCallBack);

    // exit button
    function<void()> buttonExitCallBack = bind(
        &ScreenPause::OnClickButtonExit,
        this
    );
    AddButton(buttonExit, buttonExitCallBack);

    // replay button
    function<void()> buttonReplayCallBack = bind(
        &ScreenPause::OnClickButtonReplay,
        this
    );
    AddButton(buttonReplay, buttonReplayCallBack);

    // save button
    function<void()> buttonSaveCallBack = bind(
        &ScreenPause::OnClickButtonSave,
        this
    );
    AddButton(buttonSave, buttonSaveCallBack);

    view->RenderTexture(background);
}

void ScreenPause::Redraw() {
}

ScreenType ScreenPause::Loop(SDL_Event &event) {
    if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
        int eventKey = event.key.keysym.sym;
        if (eventKey == SDLK_p) {
            return nextScreenType = BACK_TO_PREV;
        }
    }
    
    Screen::Loop(event);
    return nextScreenType;
}

void ScreenPause::OnClickButtonPlay() {
    nextScreenType = BACK_TO_PREV;
}

void ScreenPause::OnClickButtonExit() {
    nextScreenType = MAIN;
}

void ScreenPause::OnClickButtonReplay() {
    nextScreenType = PLAY;
}

void ScreenPause::OnClickButtonSave() {
    nextScreenType = SAVE;
}