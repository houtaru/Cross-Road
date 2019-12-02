#include "scene.hpp"
#include "constants.hpp"

#include <iostream>

using namespace std;

shared_ptr<View> Scene::view = View::getInstance();
shared_ptr<Sound> Scene::sound = Sound::getInstance();

const SDL_Rect Scene::RECT_BACKGOUND = {
    0, 0,
    Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT
};

Scene::Scene():
    background(),
    sceneType(),
    nextSceneType()
{
    cerr << "Constructing Scene...\n";
}

Scene::~Scene() {
    cerr << "Destructing Scene...\n";
}

shared_ptr<Scene> Scene::createSceneFromSceneType(SceneType sceneType) {
    switch (sceneType) {
        case START:
            // return shared_ptr<Scene>((Scene*) new SceneStart());
            break;
        case PLAY:
            // return shared_ptr<Scene>((Scene*) new ScenePlay());
            break;
        case PAUSE:
            // return shared_ptr<Scene>((Scene*) new ScenePause());
            break;
        case INSTRUCTION:
            // return shared_ptr<Scene>((Scene*) new SceneInstruction());
            break;
        case BEFORE_END:
            // return shared_ptr<Scene>((Scene*) new SceneBeforeEnd());
            break;
        case ENDGAME:
            // return shared_ptr<Scene>((Scene*) new SceneEndgame());
            break;
        default:
            throw "No such scene!\n";
            break;
    }
}

bool Scene::isMouseOverRect(const SDL_Rect &rect) {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    return (
        rect.x <= mouseX &&
        mouseX <= rect.x + rect.w &&
        rect.y <= mouseY &&
        mouseY <= rect.y + rect.h
    );
}

void Scene::handleMouse(function<void(Button button)> callbackRender, function<void(Button button)> callbackClick) {
    bool anyInside = false;
    for (size_t i = 0; i < buttons.size(); ++i) {
        auto button = buttons[i];
        if (isMouseOverRect(button.obj->rect)) {
            anyInside = true;
            defaultButtonState = false;
            callbackClick(button);
            if (!buttonStates[i]) {
                buttonStates[i] = true;
                callbackRender(button);
            }
        } else {
            buttonStates[i] = false;
        }
    }
}