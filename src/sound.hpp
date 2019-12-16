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
        static std::shared_ptr<Sound> getInstance();
        Sound();
        virtual ~Sound();

        // Initialize SDL_Mixer library for sound
        void initSound();

        // change state of state
        void changeState();
        
        // background music throughout the game
        void playBackgound();
        
        // the sound play when player hit obstacles
        void playDiedScene();
        
    private:
        bool state;
        static std::shared_ptr<Sound> instance;
        std::shared_ptr<Mix_Music> background;
        std::shared_ptr<Mix_Chunk> diedScene;
};