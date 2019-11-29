#include "game.hpp"
#include "exception.hpp"

#include <iostream>
#include <SDL2/SDL.h>

shared_ptr<Game> Game::instance(nullptr);
shared_ptr<View> Game::view = View::getInstance();

shared_ptr<Game> Game::getInstance() {
    if (instance == nullptr)
        instance = make_shared<Game>();
    return instance;
}

Game::Game() {
    cerr << "Constructing Game...\n";
}

Game::~Game() {
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    cerr << "Destructing Game...\n";
}

void Game::start() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        throw Exception(SDL_GetError());
    }
    cerr << "Start game...\n";
    view->startSDL();
}