#pragma once
#include "object.hpp"
#include "pointer.hpp"
#include "exception.hpp"
#include "player.hpp"

#include <vector>

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
        //  @return
        //  true if the player finishes current level
        //
        //  @param
        //  event: The event inputed by the player
        bool handlePlayer(SDL_Event &event);

        //  @brief
        //  Update position of all obstacles
        //
        //  @param
        //  level: The current level of game
        void updateObstacle(int level);

        //  @brief
        //  Check collision of player
        bool checkCollision();

        std::vector<std::shared_ptr<Texture>> getObstacles();
        std::vector<std::shared_ptr<Texture>> getStuff();
        std::shared_ptr<Texture> getPlayer();

    private:
        static const std::vector<int> posY;
        static const std::vector<std::pair<int, int>> posYcurb;

        std::shared_ptr<Object> player;

        //  Path to folder containing images of obstacles
        std::vector<std::string> obstaclePath;
        //  Path to folder containing images of stuffs
        std::vector<std::string> stuffPath;

        //  car, truck, dinosaur, bird
        std::vector<std::vector<std::shared_ptr<Object>>> obstacles;
        //  rock, tree
        std::vector<std::vector<std::shared_ptr<Object>>> stuff;
};