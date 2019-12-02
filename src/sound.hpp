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

        void initSound();
        void playBackgound();
        void playDiedScene();
    private:
        static std::shared_ptr<Sound> instance;
        std::shared_ptr<Mix_Music> background;
        std::shared_ptr<Mix_Chunk> diedScene;
};