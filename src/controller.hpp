#pragma once
#include "object.hpp"
#include "pointer.hpp"
#include "exception.hpp"
#include "player.hpp"

#include <vector>

enum SignLight { RED, YELLOW, GREEN };

class Controller {
    public:
        Controller(int level=1);
        virtual ~Controller();

        //  Data manipulations
        // void saveData();
        // void loadData();

        //  @brief
        //  Handle player character according to inputed events
        //
        //  @param
        //  event: The event inputed by the player
        //
        //  @return
        //  true if the player finishes current level
        bool HandlePlayer(SDL_Event &event);

        //  @brief
        //  Update position of all obstacles
        //
        //  @param
        //  level: The current level of game
        void Update(int level);

        //  @brief
        //  Check collision of player
        //
        //  @return
        //  true if there is a collision
        bool CheckCollision();

        std::vector<std::shared_ptr<Texture>> GetObstacles();
        std::vector<std::shared_ptr<Texture>> GetStuff();
        std::shared_ptr<Texture> GetPlayer();

    private:
        static const std::vector<int> posY;
        static const std::vector<std::pair<int, int>> posYcurb;

        //  Pointer control player
        std::shared_ptr<Object> player;

        //  Vector control sign of lights
        std::vector<SignLight> lightSigns;
        //  Vector control time of lights
        std::vector<unsigned int> lightTimes;
        //  Vector of 3 parts of light
        std::vector<SDL_Rect> lightParts;

        //  Path to folder containing images of obstacles
        std::vector<std::string> obstaclePath;
        //  Path to folder containing images of stuffs
        std::vector<std::string> stuffPath;
        //  Path to light image
        std::string lightPath;

        //  car, truck, dinosaur, bird
        std::vector<std::vector<std::shared_ptr<Object>>> obstacles;
        //  rock, tree
        std::vector<std::vector<std::shared_ptr<Object>>> stuff;
};