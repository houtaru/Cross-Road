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

        virtual void start();
        virtual void redraw();
        virtual ScreenType loop(SDL_Event &event);
    
    private:
        std::shared_ptr<Controller> controller;
        bool newGame;
        int level;

        // Update screen 
        void updateViewGround();
        // void updateViewScoring(int scoring);
};