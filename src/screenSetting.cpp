#include "constants.hpp"
#include "pointer.hpp"
#include "screenSetting.hpp"
#include <iostream>

using namespace std;

const SDL_Rect ScreenSetting::RECT_SETTING = { 700, 200, 350, 150 };
const SDL_Rect ScreenSetting::RECT_MUSIC ={400,400,350,150} ;
const SDL_Rect ScreenSetting::RECT_CHARACTER={400,550,350,150};
const SDL_Rect ScreenSetting::RECT_BUTTON_BACK = { 520, 650 , 400, 75 };
const SDL_Rect ScreenSetting::RECT_SOUND_ON = {
    600,400,100,70
};
const SDL_Rect ScreenSetting::RECT_SOUND_OFF = {
    800,400,100,70
};
const SDL_Rect ScreenSetting::RECT_CHARACTER1={
    600,500,100,150
};
const SDL_Rect ScreenSetting::RECT_CHARACTER2={
    800,500,100,150
};
ScreenSetting::ScreenSetting()
{
    //cerr << "Constructing Screen Score..\n";
    background= make_shared<Texture>(
        "assets/images/background/background_highscore.png",
        RECT_BACKGROUND
    );
    character1= make_shared<Texture>(
        "assets/images/player/player_01.png",
        RECT_CHARACTER1
    );
    character2= make_shared<Texture>(
        "assets/images/player/player_02.png",
        RECT_CHARACTER2
    );
    Setting = make_shared<FontObject>(
        "SETTING", 80, RECT_SETTING  
    ) ;
    Music = make_shared<FontObject>(
        "MUSIC", 50, RECT_MUSIC  
    ) ;
    Character = make_shared<FontObject>(
        "CHARACTER", 50, RECT_CHARACTER   
    ) ;

    buttonBack = make_shared<Texture>(
        "assets/images/button/button_back.png",
        RECT_BUTTON_BACK) ;
    function<void()> buttonBackCallBack = bind(
        &ScreenSetting::OnclickButtonBack,
        this
    );
    AddButton(buttonBack, buttonBackCallBack);
    sound_on = make_shared<FontObject>(
        "ON", 50,
        RECT_SOUND_ON
    ) ;
    sound_off = make_shared<FontObject>(
        "OFF", 50,
        RECT_SOUND_OFF
    );
}
ScreenSetting::~ScreenSetting() {
    //cerr << "Destructing screen score..\n";
}

void ScreenSetting::Start() {
    screenType = nextScreenType = SETTING;
    if (sound->getState()) view->RenderFontObject(sound_on);
    else view->RenderFontObject(sound_off);
    view->RenderTexture(background);
    view->RenderTexture(character1) ;
    view->RenderTexture(character2); 
    view->RenderFontObject(Setting, 1) ;
    view->RenderFontObject(Music, 1) ;
    view->RenderFontObject(sound_on,1 ) ;
    view->RenderFontObject(sound_off,1) ;
    view->RenderFontObject(Character,1) ; 
}

void ScreenSetting::Redraw() {}

ScreenType ScreenSetting::Loop(SDL_Event &event) {
    if (event.type == SDL_MOUSEBUTTONUP){
        if (IsMouseOverRect(RECT_SOUND_ON)){
            sound -> ChangeState(true);
        }
        if (IsMouseOverRect(RECT_SOUND_OFF)){
            sound -> ChangeState(false) ;
        }
        if (IsMouseOverRect(RECT_CHARACTER1)){
            Constants::changeCharacter(true)  ;
        }
        if (IsMouseOverRect(RECT_CHARACTER2)){
            Constants::changeCharacter(false) ; 
        }
    }
    if (screenType != nextScreenType) {
        return nextScreenType;
    }
    Screen::Loop(event) ; 
    return nextScreenType;
}
void ScreenSetting::OnclickButtonBack(){
    nextScreenType = BACK_TO_PREV;
}
void ScreenSetting::OnclickButtonTransparent(){
    nextScreenType = SETTING;
}
void ScreenSetting::UpdateViewGround() {
    view->RenderTexture(background);
}
