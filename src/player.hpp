#ifndef player_hpp
#define player_hpp

#include "object.hpp"

class Player : public Object {
    public:
        Player();
        Player(SDL_Renderer *&ren, int xSub=0, int ySub=0);
        ~Player();

        static const int VELOCITY = 5;

        //  @brief
        //  Set velocity according to the key player pressed
        //
        //  @param
        //  e: Event from player
        void SetVel(SDL_Event &e);

        //  @brief
        //  Move the player
        void Move();

        //  @brief
        //  Check whether player collide object or not
        //
        //  @param:
        //  other: Other object on screen
        bool CheckCollision(Object *&other);

    private:
        //  The velocity
        int velX, velY;
};


#endif