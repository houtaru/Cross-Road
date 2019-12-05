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
#include <glob.h>   //  glob()
#include <sstream>  //  sstrean
#include <string.h> //  memset()
#include <stdexcept>//  std::runtime_error()
#include <utility>  //  pair

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
        //  Function like glob.glob() in Python
        //
        //  @return
        //  The vector of path to all files and folders in that folder
        //  
        //  @param
        //  path: The path to specific folder
        std::vector<std::string> Glob(const std::string &path);

        //  @brief
        //  Check whether new random object's position overlaps other objects' position or not
        //
        //  @param
        //  objects: Vector of objects
        //  newObjects: THe new random object
        bool CheckOverlap(std::vector<Object*> &objects, Object *&newObject);

        //  @brief
        //  Load textures and sounds from files
        void LoadMedia(
            std::string groundPath="", 
            std::string playerPath="", 
            std::string obstaclePath="", 
            std::string stuffPath="",
            std::string musicPath="",
            std::string diesoundPath=""
        );

        //  @brief
        //  Thread renders objects
        // 
        //  @param
        //  i: The i-th thread
        int ThreadRender(int i);

        //  #brief
        //  Thread checks collision
        //
        //  @param
        //  i: The i-th thread
        int ThreadCheckCollision(int i);

        //  @brief
        //  Run game
        void Run();

    private:
        SDL_Window *window;
        SDL_Renderer *renderer;

        //  The texture
        Texture *ground;
        Object *player;

        //  Link to dynamic textures
        std::vector<std::string> obstaclePath;
        //  Link to stuff
        std::vector<std::string> stuffPath;

        //  Vectors control stuffs
        std::vector<std::vector<Object*>> stuff;
        //  Vectors control objects on lanes
        std::vector<std::vector<Object*>> obstacle;

        //  y-coordinate position of curb
        std::pair<int, int> posYcurb[3] = { {0, 75}, {355, 445}, {715, SCREEN_HEIGHT} };
        //  y-coordinate position of lanes
        int posYlane[8] = {85, 145, 235, 295, 455, 515, 595, 655};
    
        //  The sound
        Mix_Music *music;
        Mix_Chunk *diesound;
};

#endif