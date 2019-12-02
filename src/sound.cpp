#include "sound.hpp"
#include "exception.hpp"
#include <iostream>

using namespace std;

shared_ptr<Sound> Sound::instance(nullptr);

shared_ptr<Sound> Sound::getInstance() {
    if (instance == nullptr)
        instance = make_shared<Sound>();
    return instance;
}

Sound::Sound():
    background(nullptr),
    diedScene(nullptr)
{
    cerr << "Constructing Sound...\n";
}

Sound::~Sound() {
    Mix_Quit();
    cerr << "Destructing Sound...\n";
}

void Sound::initSound() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2028 < 0))
        throw Exception(Mix_GetError());
    
    background = Pointer::createMixMusic(
        Mix_LoadMUS("assets/sounds/theme.wav")
    );
    diedScene = Pointer::createMixChunk(
        Mix_LoadWAV("assets/sounds/die.wav")
    );
    playBackgound();
}

void Sound::playBackgound() {
    if (Mix_PlayingMusic() == 0)
        Mix_PlayMusic(background.get(), -1);
}

void Sound::playDiedScene() {
    if (Mix_PlayingMusic() != 0)
        Mix_HaltMusic();
    Mix_PlayChannel(-1, diedScene.get(), 0);
}