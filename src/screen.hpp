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
    PAUSE = 2,
    INSTRUCTION = 3,
    BEFORE_END = 4,
    ENDGAME = 5,
    SETTING = 6,
    QUIT = 7,
    LOADGAME = 8
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

        static std::shared_ptr<Screen> createScreenFromScreenType(ScreenType ScreenType);

        void addButton(std::shared_ptr<Texture> buttonView, std::function<void()> onMouseClick);
        void setButtonDefault(std::shared_ptr<Texture> buttonView, std::function<void()> onMouseClick);
        void clearButton();

        virtual void start();
        virtual void redraw();
        virtual ScreenType loop(SDL_Event &event);

        ScreenType getType();

    private:
        bool buttonDefaultState;
        Button buttonDefault;
        std::vector<bool> buttonStates;
        std::vector<Button> buttons;
        
        // Check if mouse goes over rectangle
        bool isMouseOverRect(const SDL_Rect &rect);

        // Handling mouse motion
        void handleMouse(std::function<void(Button button)> callbackRender, std::function<void(Button button)> callBackClick);
};