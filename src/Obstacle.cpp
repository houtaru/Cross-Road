#include "Obstacle.hpp"
//Obstacle 
Obstacle::Obstacle(Box box, int velocity, int level){
    this -> box = box ; 
    this -> velocity = velocity ; 
    this -> level = level ; 
}
std::array<int,4> Obstacle::Position(){
    std::array<int,4> temp = box.Position() ; 
    return temp ; 
}

//Truck
Truck::Truck(Box box, int velocity, int level) : Obstacle(box,velocity,level){} 
void Truck::Move(){
    Obstacle::Move() ; 
    std::array<int,2> distance= {level*velocity,0};
    box+=distance ;
}
int Truck::Sound(){
    return 1 ; 
}
std::array<int,4> Truck::Position(){
    Obstacle::Position() ; 
}

//Car 
Car::Car(Box box, int velocity, int level) : Obstacle(box,velocity,level){} 
void Car::Move(){
    Obstacle::Move() ; 
    std::array<int,2> distance= {level*velocity,0};
    box+=distance ;
}
int Car::Sound(){
    return 2 ; 
}
std::array<int,4> Car::Position(){
    Obstacle::Position() ; 
}

//Dinasaur 
Dinasaur::Dinasaur(Box box, int velocity, int level) : Obstacle(box,velocity,level){} 
void Dinasaur::Move(){
    Obstacle::Move() ; 
    std::array<int,2> distance= {level*velocity,0};
    box+=distance ;
}
int Dinasaur::Sound(){
    return 3 ; 
}
std::array<int,4> Dinasaur::Position(){
    Obstacle::Position() ; 
}

//Bird 
Bird::Bird(Box box, int velocity, int level) : Obstacle(box,velocity,level){} 
void Bird::Move(){
    Obstacle::Move() ; 
    std::array<int,2> distance= {level*velocity,0};
    box+=distance ;
}
int Bird::Sound(){
    return 4 ; 
}
std::array<int,4> Bird::Position(){
    Obstacle::Position() ; 
}


