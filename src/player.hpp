#pragma once
#include "object.hpp"

class Player: public Object {
    public:
        Player();
        Player(std::string path, SDL_Rect rect, bool _flip = false);
        virtual ~Player();

        //  @brief
        //  Set velocity according to the key player pressed
        //
        //  @param
        //  event: Event from player
        void setVel(SDL_Event &event);
        
        //  @brief
        //  Move the player
        //
        //  @param
        //  stuff: Vector of stuffs to not overlap
        bool canMove(std::vector<std::vector<std::shared_ptr<Object>>> &stuff);

    private:
        //  The velocity
        int velX, velY;
};