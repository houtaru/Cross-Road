#pragma once
#include "screen.hpp"

#include <map>
// #include <mutex>
// #include <thread>

class ScreenPlay: public Screen {
    typedef void (ScreenPlay::*FunctionPointer)();
    public:
        ScreenPlay();
        virtual ~ScreenPlay();

        virtual void Start();
        virtual void Redraw();
        virtual ScreenType Loop(SDL_Event &event);
    
        int NormalScore(int time, int level);
    
    private:
        std::shared_ptr<Controller> controller;
        std::shared_ptr<FontObject> fontLevel;
        std::shared_ptr<FontObject> fontScore;
    
        static const SDL_Rect RECT_LEVEL;
        static const SDL_Rect RECT_SCORE;
    
        bool newGame;
        int level;
        int startTime;
        int finalScore;
    
        // Update screen 
        void UpdateViewGround();
};
