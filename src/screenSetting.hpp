#pragma once
#include "screen.hpp"
#include <fstream> 
#include <vector>
#include <map>
// #include <mutex>
// #include <thread>
class ScreenSetting: public Screen{
    typedef void (ScreenSetting::*FunctionPointer)();
    public:
        ScreenSetting();
        virtual ~ScreenSetting();
        virtual void Start();
        virtual void Redraw();
        virtual ScreenType Loop(SDL_Event &event);
        void OnclickButtonBack() ;
        void OnclickButtonTransparent() ;

    private:
        std::shared_ptr<FontObject> Music;
        std::shared_ptr<FontObject> Character;
        std::shared_ptr<FontObject> Setting ; 
        void UpdateViewGround();
        static const SDL_Rect RECT_BUTTON_BACK;
        static const SDL_Rect RECT_SOUND_ON;
        static const SDL_Rect RECT_SOUND_OFF ;
        std::shared_ptr<FontObject> sound_on;
        std::shared_ptr<FontObject> sound_off;

        void handleMouseRect();
        static const SDL_Rect RECT_MUSIC;
        static const SDL_Rect RECT_CHARACTER;
        static const SDL_Rect RECT_CHARACTER1;
        static const SDL_Rect RECT_CHARACTER2;
        static const SDL_Rect RECT_SETTING ; 
        // void updateViewScoring(int scoring);
        std::shared_ptr<Texture> buttonBack;
        std::shared_ptr<Texture> buttonMusic; 
        std::shared_ptr<Texture> character1 ; 
        std::shared_ptr<Texture> character2 ;

};
