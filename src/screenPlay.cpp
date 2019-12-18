#include "screenPlay.hpp"
#include "constants.hpp"
#include "pointer.hpp"

#include <fstream>
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

const SDL_Rect ScreenPlay::RECT_LEVEL = { 1150, 0, 350, 150};
const SDL_Rect ScreenPlay::RECT_SCORE = { 1400, 0, 350, 150};

ScreenPlay::ScreenPlay(bool newGame) :
    level(1), startTime(0), finalScore(0)
{
    background = make_shared<Texture>(
        "assets/images/ground/ground_01.png",
        RECT_BACKGROUND
    );
    
    if (newGame) 
        controller = make_shared<Controller>(level, Constants::boy);
    else 
        controller = make_shared<Controller>(level, finalScore);

    string s = "LEVEL " + to_string(level);
    fontLevel = make_shared<FontObject>(s, 40, RECT_LEVEL);
    s = "SCORE " + to_string(finalScore);
    fontScore = make_shared<FontObject>(s, 40, RECT_SCORE);

    //cerr << "Constructing Screen Play....\n";
}

ScreenPlay::~ScreenPlay() {
    ifstream fin ;
    fin.open("data/score.txt") ;
    int x ;
    vector<int> score ;
    for (int i = 0; i < 5; i++) {
        fin >> x ;
        score.push_back(x);
    }
    score.push_back(finalScore);
    sort(score.begin(),score.end(), greater<>());
    fin.close();
    
    ofstream fout;
    fout.open("data/score.txt") ;
    for (int i = 0; i < 5; i++)
        fout << score[i] << endl ;
    fout.close() ;
    //cerr << "Destructing Screen Play...\n";
}

void ScreenPlay::Start() {
    screenType = nextScreenType = PLAY;
    view->RenderClear();
    ClearButton();
    SetButtonDefault(background, nullptr);

    view->RenderTexture(background);
    startTime = SDL_GetTicks();
}

void ScreenPlay::Redraw() {
    UpdateViewGround();
}

ScreenType ScreenPlay::Loop(SDL_Event &event) {
    if (screenType != nextScreenType) {
        return nextScreenType;
    }
    if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
        int eventKey = event.key.keysym.sym;
        switch (eventKey) {
            case SDLK_ESCAPE:
                return nextScreenType = PAUSE;
            default:
                //  If player finishes the current level
                if (controller->HandlePlayer(event)) {
                    finalScore += NormalScore(SDL_GetTicks() - startTime, level);
                    ++level;
                    
                    //  Game just has 5 levels. If complete all of them, CONGRATULATION, YOU WIN
                    if (level > 5) {
                        cerr << "You win!\n";
                        return BACK_TO_PREV;
                    }
                    
                    //  Update score and level display
                    string s = "LEVEL " + to_string(level);
                    fontLevel = make_shared<FontObject>(s, 40, RECT_LEVEL);
                    s = "SCORE " + to_string(finalScore);
                    fontScore = make_shared<FontObject>(s, 40, RECT_SCORE);
                    
                    //  Reset controller for new level
                    controller = make_shared<Controller>(level, Constants::boy);
                    //  Start again
                    Start();
                }
        }
    }

    if (controller->CheckCollision()) {
        nextScreenType = BACK_TO_PREV;
        sound->PlayDiedScene();
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
    return nextScreenType;
}

int ScreenPlay::NormalScore(int time, int level) {
    if (level*1000 - time/50 > 0)
        return level*1000 - time/50;
    else
        return 0;
}

void ScreenPlay::Save() {
    controller->Save(level, finalScore);
}

void ScreenPlay::UpdateViewGround() {
    controller->Update(level);

    view->RenderTexture(background);
    view->RenderTexture(controller->GetObstacles());
    view->RenderTexture(controller->GetStuff());
    view->RenderTexture(controller->GetPlayer());
    
    view->RenderFontObject(fontLevel, 2);
    view->RenderFontObject(fontScore, 2);
}
