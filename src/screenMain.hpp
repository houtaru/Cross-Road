#pragma once
#include "screen.hpp"

class ScreenMain: public Screen {
    public:
        ScreenMain();
        virtual ~ScreenMain();

        void Start();
        void Redraw();
        ScreenType Loop(SDL_Event &event);

        // Bind later to callback function when click `Start`
        void OnClickButtonStart();
        // Bind later to callback function when click `LoadGame`
        void OnClickButtonLoadGame();
        // Bind later to callback function when click `Highscore`
        void OnClickButtonHighscore();
        // Bind later to callback function when click `Setting`
        void OnClickButtonSetting();
        // Bind later to callback function when click `Quit`
        void OnClickButtonQuit();

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
