#pragma once
#include "screen.hpp"
#include <fstream> 
#include <vector>
#include <map>
// #include <mutex>
// #include <thread>

class ScreenScore: public Screen {
    typedef void (ScreenScore::*FunctionPointer)();
    public:
        ScreenScore();
        virtual ~ScreenScore();
        virtual void Start();
        virtual void Redraw();
        virtual ScreenType Loop(SDL_Event &event);
        void OnclickButtonBack() ;

    private:
        std::vector<int> score ; 
        std::shared_ptr<FontObject> fontHighScore;
        std::shared_ptr<FontObject> temp;

        std::vector<std::shared_ptr<FontObject>> fontScore;

        void UpdateViewGround();
        static const SDL_Rect RECT_BUTTON_BACK;

        static const SDL_Rect RECT_HIGHSCORE;
        static const SDL_Rect RECT_SCORE1;
        static const SDL_Rect RECT_SCORE2;
        static const SDL_Rect RECT_SCORE3;
        static const SDL_Rect RECT_SCORE4;
        static const SDL_Rect RECT_SCORE5;
        std::vector<SDL_Rect> Rect = {RECT_SCORE1 , RECT_SCORE2 , RECT_SCORE3 , RECT_SCORE4, RECT_SCORE5}; 

        // void updateViewScoring(int scoring);
        std::shared_ptr<Texture> buttonBack;

};