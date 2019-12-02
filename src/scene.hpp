#pragma once
#include "view.hpp"
#include "sound.hpp"
#include "object.hpp"

#include <vector>

using namespace std;

enum SceneType {
    BACK_TO_PREV = -1,
    START = 0,
    PLAY = 1,
    PAUSE = 2,
    INSTRUCTION = 3,
    BEFORE_END = 4,
    ENDGAME = 5
};

class Scene {
    public:
        static shared_ptr<View> view;
        static shared_ptr<Sound> sound;
        static const SDL_Rect RECT_BACKGOUND;
        
        shared_ptr<Object> background;
        SceneType sceneType, nextSceneType;


        Scene();
        virtual ~Scene();

        static shared_ptr<Scene> createSceneFromSceneType(SceneType sceneType);

    private:
        bool defaultButtonState;
        Button buttonDefault;
        std::vector<bool> buttonStates;
        std::vector<Button> buttons;
        
        bool isMouseOverRect(const SDL_Rect &rect);
        void handleMouse(function<void(Button button)> callbackRender, function<void(Button button)> callBackClick);
};