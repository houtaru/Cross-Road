#include "box.hpp"
#include "array"
class Obstacle{
protected:
    Box box ; 
    int velocity ;
    static int level ; 
public:
    Obstacle() = default ;
    Obstacle(Box box,int velocity , int levl) ; 
    virtual void Move() = 0 ;
    virtual int Sound() =0 ; 
    virtual std::array<int,4> Position() ;
};
class Truck :public Obstacle{
public:
    Truck() = default; 
    Truck(Box box, int velocity, int level); 
    void Move(); 
    int Sound() ; 
    std::array<int,4> Position() ;
} ;
class Car: public Obstacle{
public:
    Car() = default;
    Car(Box box, int velocity, int level); 
    void Move() ; 
    int Sound() ; 
    std::array<int,4> Position() ;
};
class Dinasaur: public Obstacle{
public:
    Dinasaur() = default ;
    Dinasaur(Box box, int velocity, int level); 
    void Move() ; 
    int Sound() ;
    std::array<int,4> Position() ;
};
class Bird: public Obstacle{
public:
    Bird() = default ; 
    Bird(Box box, int velocity , int level) ; 
    void Move() ; 
    int Sound() ; 
    std::array<int,4> Position() ;
};
