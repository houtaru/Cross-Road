#include "game.hpp"
#include "exception.hpp"

#include <iostream>
#include <thread>
#include <chrono>
#ifdef __APPLE__
    #include <SDL.h>
#else
    #include <SDL2/SDL.h>
#endif

using namespace std;

shared_ptr<Game> Game::instance(nullptr);
shared_ptr<View> Game::view = View::GetInstance();
shared_ptr<Sound> Game::sound = Sound::GetInstance();

const int Game::FRAME_PER_SECOND = 60;
const int Game::SDL_DELAY_PER_FRAME = 1000 / FRAME_PER_SECOND;

shared_ptr<Game> Game::GetInstance() {
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
    //cerr << "Constructing Game...\n";
}

Game::~Game() {
    //cerr << "Destructing Game...\n";
}

void Game::Start() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        throw Exception(SDL_GetError());
    }
    //cerr << "Start game...\n";
    Init();
    Loop();
}

void Game::Init() {
    //cerr << "  Game initalization..\n";
    view->StartSDL();
    sound->InitSound();
    
    screens.push_back(Screen::CreateScreenFromScreenType(MAIN));
    screens.back()->Start();
    running = true;
    view->RenderPresent();
}

void Game::Loop() {
    //cerr << "  Game loop...\n";
    keystate = SDL_GetKeyboardState(NULL);

    using FrameDuration = std::chrono::duration<int, ratio<1, 60>>;
    auto next_start = std::chrono::steady_clock::now() + FrameDuration{1};

    while (running) {
        do {
            if (event.type == SDL_QUIT) {
                running = false;
                return;
            }

            ScreenType nextScreenType = screens.back()->Loop(event);
            if (nextScreenType != screens.back()->GetType()) {
                if (nextScreenType == BACK_TO_PREV) {
                    //cerr << "Back to previous screen!\n";
                    BackToPreScr();
                } else if (nextScreenType != QUIT) {
                    //cerr << "Switch to next screen.\n";
                    SwitchToNextScr(nextScreenType);
                } else {
                    running = false;
                }
            }
            SDL_PumpEvents();
        } while (SDL_PollEvent(&event) != 0 && running);

        screens.back()->Redraw();
        view->RenderPresent();
        std::this_thread::sleep_until(next_start);
        next_start += FrameDuration{1};
    }
}

const Uint8 *Game::GetKeystate() {
    return keystate;
}

void Game::BackToPreScr() {
    screens.pop_back();
    if (screens.empty()) {
        running = false;
        return;
    }
    screens.back()->Start();
}

void Game::SwitchToNextScr(ScreenType nextScreenType) {
    screens.push_back(Screen::CreateScreenFromScreenType(nextScreenType));
    screens.back()->Start();
}
