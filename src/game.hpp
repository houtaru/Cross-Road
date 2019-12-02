#ifndef game_hpp
#define game_hpp

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include <string>   //  std::string
#include <vector>   //  std::vector
#include <ctime>    //  time()
#include <cstdlib>  //  srand(), rand()
#include <thread>   //  thread
#include <future>   //  std::future, std::async
#include "constant.hpp"
#include "texture.hpp"
#include "object.hpp"
#include "player.hpp"

enum ObstacleLane {
    LANE1,
    LANE2,
    LANE3,
    LANE4,
    LANE5,
    LANE6,
    LANE7,
    LANE8
};
enum TypeObject {
    TRUCK,
    CAR
};

class Game {
    public:
        Game();
        ~Game();


        //  @brief
        //
        //  Check whether new random object's position overlaps other objects' position or not
        bool CheckOverlap(const std::vector<Object*> &lane, int random);

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
        //  Thread renders objects
        int ThreadRender(int i);

        //  #brief
        //  Thread checks collision
        int ThreadCheckCollision(int i);

        //  @brief
        //  Run game
        void Run();

    private:
        SDL_Window *window;
        SDL_Renderer *renderer;

        //  The texture
        Texture *ground;
        Player *player;

        //  Link to dynamic textures
        std::string truckPath;
        std::string carPath;

        //  Vectors control objects on lanes
        std::vector<std::vector<Object*>> obstacle;

        //  y-coordinate position of lanes
        int posY[8] = {85, 145, 235, 295, 455, 515, 595, 655};
        
        //  The sound
        Mix_Music *music;
        Mix_Chunk *diesound;
};

#endif