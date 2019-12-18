#include "sound.hpp"
#include "exception.hpp"
#include <iostream>

using namespace std;

shared_ptr<Sound> Sound::instance(nullptr);

shared_ptr<Sound> Sound::GetInstance() {
    if (instance == nullptr)
        instance = make_shared<Sound>();
    return instance;
}

Sound::Sound():
    state(true),
    background(nullptr),
    diedScene(nullptr)
{
    //cerr << "Constructing Sound...\n";
}

Sound::~Sound() {
    Mix_Quit();
    //cerr << "Destructing Sound...\n";
}

void Sound::InitSound() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2028 < 0))
        throw Exception(Mix_GetError());
    
    background = Pointer::CreateMixMusic(
        Mix_LoadMUS("assets/sounds/theme.wav")
    );
    diedScene = Pointer::CreateMixChunk(
        Mix_LoadWAV("assets/sounds/die.wav")
    );
    PlayBackgound();
}

void Sound::PlayBackgound() {
    if (!state) return;
    if (Mix_PlayingMusic() == 0)
        Mix_PlayMusic(background.get(), -1);
}

void Sound::PlayDiedScene() {
    if (!state) return;
    // if (Mix_PlayingMusic() != 0)
    //     Mix_HaltMusic();
    Mix_PlayChannel(-1, diedScene.get(), 0);
}
bool Sound::getState() {
    return state;
} 	
void Sound::ChangeState(bool sound_on) {
    state = sound_on ;
    if (Mix_PlayingMusic() != 0 && !state ) 
        Mix_HaltMusic();
    if (state && !Mix_PlayingMusic())
        PlayBackgound() ;
}