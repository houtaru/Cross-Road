#pragma once
#include "screen.hpp"

#include <map>
#include <mutex>
#include <thread>

class ScreenPlay: public Screen {
    typedef void (ScreenPlay::*FunctionPointer)();
    public:
        ScreenPlay();
        virtual ~ScreenPlay();

        virtual void start();
        virtual void redraw();
        virtual ScreenType loop(SDL_Event &event);
    
    private:
        static std::mutex eventMutex;

        bool newGame;
        std::map<int, FunctionPointer> eventMap;
        int level;
        // Control
        void handleButtonArrowDown();
        void handleButtonArrowUp();
        void handleButtonArrowLeft();
        void handleButtonArrowRight();
        void handleButtonEscape();
        void handleButtonSpace();
        void handleButtonP();

        // Update screen 
        void updateViewGround();
        // void updateViewScoring(int scoring);
};