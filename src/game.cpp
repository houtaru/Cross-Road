#include "game.hpp"
#include "exception.hpp"

#include <iostream>
#include <thread>
#ifdef __APPLE__
    #include <SDL.h>
#else
    #include <SDL2/SDL.h>
#endif

using namespace std;

shared_ptr<Game> Game::instance(nullptr);
shared_ptr<View> Game::view = View::getInstance();
shared_ptr<Sound> Game::sound = Sound::getInstance();

const int Game::FRAME_PER_SECOND = 60;
const int Game::SDL_DELAY_PER_FRAME = 1000 / FRAME_PER_SECOND;

shared_ptr<Game> Game::getInstance() {
    if (instance == nullptr)
        instance = make_shared<Game>();
    return instance;
}

Game::Game():
    running(false),
    screens(),
    event(),
    keystate() 
{
    cerr << "Constructing Game...\n";
}

Game::~Game() {
    cerr << "Destructing Game...\n";
}

void Game::start() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        throw Exception(SDL_GetError());
    }
    cerr << "Start game...\n";
    init();
    loop();
}

void Game::init() {
    cerr << "  Game initalization..\n";
    view->startSDL();
    sound->initSound();
    
    screens.push_back(Screen::createScreenFromScreenType(MAIN));
    screens.back()->start();
    running = true;
    view->renderPresent();
}

void Game::loop() {
    cerr << "  Game loop...\n";
    keystate = SDL_GetKeyboardState(NULL);

    using FrameDuration = std::chrono::duration<int, ratio<1, 60>>;
    auto next_start = std::chrono::steady_clock::now() + FrameDuration{1};

    while (running) {
        while (SDL_PollEvent(&event) != 0 && running) {
            SDL_PumpEvents();
            if (event.type == SDL_QUIT) {
                running = false;
                return;
            }

            ScreenType nextScreenType = screens.back()->loop(event);
            if (nextScreenType != screens.back()->getType()) {
                if (nextScreenType == BACK_TO_PREV) {
                    cerr << "Back to previous screen!\n";
                    backToPreScr();
                } else if (nextScreenType != QUIT) {
                    cerr << "Switch to next screen.\n";
                    switchToNextScr(nextScreenType);
                } else {
                    running = false;
                }
            }
            view->renderPresent();
        }
        screens.back()->redraw();
        view->renderPresent();
        
        std::this_thread::sleep_until(next_start);
        next_start += FrameDuration{1};
    }
}

const Uint8 *Game::getKeystate() {
    return keystate;
}

void Game::backToPreScr() {
    screens.pop_back();
    if (screens.empty()) {
        running = false;
        return;
    }
    screens.back()->start();
}

void Game::switchToNextScr(ScreenType nextScreenType) {
    screens.push_back(Screen::createScreenFromScreenType(nextScreenType));
    screens.back()->start();
}
