#include "screenScore.hpp"
#include "constants.hpp"
#include "pointer.hpp"

#include <iostream>

using namespace std;

const SDL_Rect ScreenScore::RECT_BUTTON_BACK = { 540, 650 , 325, 75 };
const SDL_Rect ScreenScore::RECT_HIGHSCORE = { 700, 200, 350, 150 };
const SDL_Rect ScreenScore::RECT_SCORE1 = { 700, 300, 350, 150 };
const SDL_Rect ScreenScore::RECT_SCORE2 = { 700, 375, 350, 150 };
const SDL_Rect ScreenScore::RECT_SCORE3 = { 700, 450, 350, 150 };
const SDL_Rect ScreenScore::RECT_SCORE4 = { 700, 525, 350, 150 };
const SDL_Rect ScreenScore::RECT_SCORE5 = { 700, 600, 350, 150 };

ScreenScore::ScreenScore()
{
    //cerr << "Constructing Screen Score..\n";
    background= make_shared<Texture>(
        "assets/images/background/background_highscore.png",
        RECT_BACKGROUND
    );
}
ScreenScore::~ScreenScore() {
    //cerr << "Destructing screen score..\n";
}

void ScreenScore::Start() {
    screenType = nextScreenType = HIGHSCORE;

    view->RenderClear();
    ClearButton();
    SetButtonDefault(background, nullptr);
    
    fontHighScore = make_shared<FontObject>(
        "HIGH SCORE", 80, RECT_HIGHSCORE 
    ) ;
    ifstream fin; 
    fin.open("data/score.txt") ; 
    int x ; 
    for (int i = 0; i < 5; i++)
        {
            fin >> x ;
            score.push_back(x);
        }
    sort(score.begin(), score.end(), greater<>());
    fin.close(); 
    buttonBack = make_shared<Texture>(
        "assets/images/button/button_back.png",
        RECT_BUTTON_BACK) ;
    function<void()> buttonStartCallBack = bind(
        &ScreenScore::OnclickButtonBack,
        this
    );
    AddButton(buttonBack, buttonStartCallBack);

    for (int i = 0; i < 5; i++) {
        string s = to_string(score[i]);  
        temp  = make_shared<FontObject>(s, 30 , Rect[i]);
        fontScore.push_back(temp);
    }
    view->RenderTexture(background);
    view->RenderFontObject(fontHighScore, 1);
    view->RenderFontObject(fontScore, 1);
}

void ScreenScore::Redraw() {
}

ScreenType ScreenScore::Loop(SDL_Event &event) {
    if (screenType != nextScreenType) {
        return nextScreenType;
    }
    Screen::Loop(event); 
    return nextScreenType;
}
void ScreenScore::OnclickButtonBack(){
    nextScreenType = BACK_TO_PREV;
}
void ScreenScore::UpdateViewGround() {
    view->RenderTexture(background);
}
