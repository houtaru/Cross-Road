#pragma once
#include "object.hpp"

class Player: public Object {
    public:
        Player();
        virtual ~Player();
        
        //  @brief
        //  Move the player
        //
        //  @param
        //  stuff: Vector of stuffs to not overlap
        bool canMove(std::vector<std::vector<std::shared_ptr<Object>>> &stuff);
};