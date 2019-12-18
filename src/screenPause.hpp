#pragma once
#include "screen.hpp"

class ScreenPause: public Screen {
    public:
        ScreenPause();
        virtual ~ScreenPause();

        virtual void Start();
        virtual void Redraw();
        virtual ScreenType Loop(SDL_Event &event);

    public:
        static const SDL_Rect RECT_BUTTON_PLAY;
        static const SDL_Rect RECT_BUTTON_EXIT;
        static const SDL_Rect RECT_BUTTON_REPLAY;
        static const SDL_Rect RECT_BUTTON_SAVE;
        static const SDL_Rect RECT_BACKGROUND_PAUSE;
        static const SDL_Rect RECT_TEXT_PAUSE;

        std::shared_ptr<Texture> buttonPlay;
        std::shared_ptr<Texture> buttonExit;
        std::shared_ptr<Texture> buttonReplay;
        std::shared_ptr<Texture> buttonSave;

        void OnClickButtonPlay();
        void OnClickButtonExit();
        void OnClickButtonReplay();
        void OnClickButtonSave();
};