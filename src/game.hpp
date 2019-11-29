#ifndef game_hpp
#define game_hpp

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <string>
#include "constant.hpp"
#include "texture.hpp"
#include "object.hpp"
#include "player.hpp"

class Game {
    public:
        Game();
        ~Game();

        //  @brief
        //  Load textures and sounds from files
        void LoadMedia(
            std::string groundPath="", 
            std::string playerPath="", 
            std::string carPath="", 
            std::string truckPath="",
            std::string musicPath="",
            std::string diesoundPath=""
        );

        //  @brief
        //  Run game
        void Run();

    private:
        SDL_Window *window;
        SDL_Renderer *renderer;

        //  The texture
        Texture *ground;
        Object *car;
        Object *truck;
        Player *player;

        
        //  The sound
        Mix_Music *music;
        Mix_Chunk *diesound;
};

#endif