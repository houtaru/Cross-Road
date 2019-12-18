#pragma once
#include "view.hpp"
#include "sound.hpp"
#include "object.hpp"
#include "controller.hpp"

#include <vector>

enum ScreenType {
    BACK_TO_PREV = -1,
    MAIN = 0,
    PLAY = 1,
    LOAD = 2,
    HIGHSCORE = 3,
    SETTING = 4,
    QUIT = 5,
    PAUSE = 6,
    SAVE = 7
};

class Screen {
    public:
        static std::shared_ptr<View> view;
        static std::shared_ptr<Sound> sound;
        static const SDL_Rect RECT_BACKGROUND;
        
        std::shared_ptr<Texture> background;
        ScreenType screenType, nextScreenType;

        Screen();
        virtual ~Screen();

        static std::shared_ptr<Screen> CreateScreenFromScreenType(ScreenType ScreenType);

        void AddButton(std::shared_ptr<Texture> buttonView, std::function<void()> onMouseClick);
        void SetButtonDefault(std::shared_ptr<Texture> buttonView, std::function<void()> onMouseClick);
        void ClearButton();

        virtual void Start();
        virtual void Redraw();
        virtual ScreenType Loop(SDL_Event &event);
        virtual void Save();

        ScreenType GetType();

    protected:
        bool buttonDefaultState;
        Button buttonDefault;
        std::vector<bool> buttonStates;
        std::vector<Button> buttons;
        
        // Check if mouse goes over rectangle
        bool IsMouseOverRect(const SDL_Rect &rect);

        // Handling mouse motion
        void HandleMouse(std::function<void(Button button)> callbackRender, std::function<void(Button button)> callBackClick);
};