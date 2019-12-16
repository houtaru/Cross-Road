#include "screenMain.hpp"
#include "constants.hpp"

#include <iostream>

using namespace std;

const SDL_Rect ScreenMain::RECT_BUTTON_START = {
    Constants::SCREEN_WIDTH / 2 - 350 / 2,
    Constants::SCREEN_HEIGHT / 3 - 5,
    350, 92
};
const SDL_Rect ScreenMain::RECT_BUTTON_LOADGAME = {
    Constants::SCREEN_WIDTH / 2 - 300 / 2,
    RECT_BUTTON_START.y + RECT_BUTTON_START.h + 45,
    300, 60
};

const SDL_Rect ScreenMain::RECT_BUTTON_HIGHSCORE = {
    RECT_BUTTON_LOADGAME.x,
    RECT_BUTTON_LOADGAME.y + RECT_BUTTON_LOADGAME.h + 25,
    300, 60
};

const SDL_Rect ScreenMain::RECT_BUTTON_SETTING = {
    RECT_BUTTON_HIGHSCORE.x,
    RECT_BUTTON_HIGHSCORE.y + RECT_BUTTON_HIGHSCORE.h + 25,
    300, 60
};

const SDL_Rect ScreenMain::RECT_BUTTON_QUIT = {
    RECT_BUTTON_SETTING.x,
    RECT_BUTTON_SETTING.y + RECT_BUTTON_SETTING.h + 23,
    300, 60
};

ScreenMain::ScreenMain():
    buttonStart(new Texture(
        "assets/images/button/button_start.png",
        RECT_BUTTON_START
    )),
    buttonLoad(new Texture(
        "assets/images/button/button_loadgame.png",
        RECT_BUTTON_LOADGAME
    )),
    buttonHighscore(new Texture(
        "assets/images/button/button_highscore.png",
        RECT_BUTTON_HIGHSCORE
    )),
    buttonSetting(new Texture(
        "assets/images/button/button_setting.png",
        RECT_BUTTON_SETTING
    )),
    buttonQuit(new Texture(
        "assets/images/button/button_quit.png",
        RECT_BUTTON_QUIT
    ))
{
    background = make_shared<Texture>("assets/images/background/background.png", RECT_BACKGROUND);
    //cerr << "Construction main screen.\n";
}

ScreenMain::~ScreenMain() {
    //cerr << "Destructing main screen.\n";
}

void ScreenMain::start() {
    screenType = nextScreenType = MAIN;
    view->renderTexture(background);

    clearButton();
    setButtonDefault(background, nullptr);
    
    // start button
    function<void()> buttonStartCallBack = bind(
        &ScreenMain::onClickButtonStart,
        this
    );
    addButton(buttonStart, buttonStartCallBack);

    // load game button
    function<void()> buttonLoadGameCallBack = bind(
        &ScreenMain::onClickButtonLoadGame,
        this
    );
    addButton(buttonLoad, buttonLoadGameCallBack);

    // highscore button
    function<void()> buttonHighscoreCallBack = bind(
        &ScreenMain::onClickButtonHighscore,
        this
    );
    addButton(buttonHighscore, buttonHighscoreCallBack);
    
    // setting button
    function<void()> buttonSettingCallBack = bind(
        &ScreenMain::onClickButtonSetting,
        this
    );
    addButton(buttonSetting, buttonSettingCallBack);
    
    // quit button
    function<void()> buttonQuitCallBack = bind(
        &ScreenMain::onClickButtonQuit,
        this
    );
    addButton(buttonQuit, buttonQuitCallBack);
}

void ScreenMain::redraw() {
}

ScreenType ScreenMain::loop(SDL_Event &event) {
    Screen::loop(event);
    return nextScreenType;
}

void ScreenMain::onClickButtonStart() {
    nextScreenType = PLAY;
}

void ScreenMain::onClickButtonLoadGame() {
    nextScreenType = LOADGAME;
}

void ScreenMain::onClickButtonHighscore() {
    nextScreenType = ENDGAME;
}

void ScreenMain::onClickButtonSetting() {
    nextScreenType = SETTING;
}

void ScreenMain::onClickButtonQuit() {
    nextScreenType = QUIT;
}

