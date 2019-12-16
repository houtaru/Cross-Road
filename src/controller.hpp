#pragma once
#include "object.hpp"
#include "pointer.hpp"
#include "exception.hpp"
#include "player.hpp"

#include <vector>

class Controller {
    public:
        static std::shared_ptr<Controller> getInstance();

        Controller(int level=1);
        virtual ~Controller();

        // main functions
        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();
        void clearAll();
        bool collision();

        // Data manipulations
        // void saveData();
        // void loadData();

        void updateObstacle(int level);

        std::vector<std::shared_ptr<Texture>> getObstacles();
        std::vector<std::shared_ptr<Texture>> getStuff();

        // concurrence
        // bool checkCollision(); 

    private:
        static std::shared_ptr<Controller> instance;
        
        static const std::vector<int> posY;
        static const std::vector<std::pair<int, int>> posYcurb;

        std::shared_ptr<Player> player;

        std::vector<std::string> obstaclePath;
        std::vector<std::string> stuffPath;

        std::vector<std::vector<std::shared_ptr<Object>>> obstacles; // car, truck, dinosaur, bird
        std::vector<std::vector<std::shared_ptr<Object>>> stuff; // rock, tree
};