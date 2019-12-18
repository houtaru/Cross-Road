#pragma once
#include "pointer.hpp"
#include <memory>
#ifdef __APPLE__
    #include <SDL_mixer.h>
#else
    #include <SDL2/SDL_mixer.h>
#endif

class Sound {
    public:
        static std::shared_ptr<Sound> GetInstance();
        Sound();
        virtual ~Sound();

        // Initialize SDL_Mixer library for sound
        void InitSound();

        // change state of state
        void ChangeState(bool sound_on);
        bool getState();

        // background music throughout the game
        void PlayBackgound();
        
        // the sound play when player hit obstacles
        void PlayDiedScene();
        
    private:
        bool state;
        static std::shared_ptr<Sound> instance;
        std::shared_ptr<Mix_Music> background;
        std::shared_ptr<Mix_Chunk> diedScene;
};