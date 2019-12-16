#pragma once
#include "screen.hpp"

class ScreenMain: public Screen {
    public:
        ScreenMain();
        virtual ~ScreenMain();

        void start();
        void redraw();
        ScreenType loop(SDL_Event &event);

        // Bind later to callback function when click `Start`
        void onClickButtonStart();

        // Bind later to callback function when click `Load Game`
        void onClickButtonLoadGame();

        // Bind later to callback function when click `Highscore`
        void onClickButtonHighscore();

        // // Bind later to callback function when click `Setting`
        void onClickButtonSetting();

        // Bind later to callback function when click `Quit`
        void onClickButtonQuit();

    private:
        static const SDL_Rect RECT_BUTTON_START;
        static const SDL_Rect RECT_BUTTON_LOADGAME;
        static const SDL_Rect RECT_BUTTON_HIGHSCORE;
        static const SDL_Rect RECT_BUTTON_SETTING;
        static const SDL_Rect RECT_BUTTON_QUIT;

        std::shared_ptr<Texture> buttonStart;
        std::shared_ptr<Texture> buttonLoad;
        std::shared_ptr<Texture> buttonHighscore;
        std::shared_ptr<Texture> buttonSetting;
        std::shared_ptr<Texture> buttonQuit;
};
