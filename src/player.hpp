#ifndef player_hpp
#define player_hpp

#include "object.hpp"
#include <vector>

class Player : public Object {
    public:
        Player();
        Player(SDL_Renderer *&ren, int xSub=0, int ySub=0);
        ~Player();

        static const int VELOCITY = 6;

        //  @brief
        //  Set velocity according to the key player pressed
        //
        //  @param
        //  e: Event from player
        void SetVel(SDL_Event &e);

        //  @brief
        //  Move the player
        //
        //  @param
        //  stuff: Vector of stuffs to not overlap
        bool Move(std::vector<std::vector<Object*>> &stuff);

    private:
        //  The velocity
        int velX, velY;
};


#endif