#ifndef PLAYER_HPP_DEFINED
#define PLAYER_HPP_DEFINED

#include <box.hpp>
#include <obstacle.hpp>

#include <memory>


// In file include/player.hpp
// @note:
//      - Add sound in front-end
class Player {
    public:
        Player() {}
        Player(const Box& _box): box(_box) {
        }
        Player(const Player& p) {
            this->box = p.box;
        }
        
        ~Player(){}

        Box position();

        void move(array<int, 2>);


    private:
        Box box;
};

#endif // PLAYER_HPP_DEFINED
