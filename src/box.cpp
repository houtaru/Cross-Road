#include "box.hpp"

Box::Box() { x1 = x2 = y1 = y2 = 0; }
Box::Box(const Box &other) {}
Box::~Box() {}

array<int, 4> Box::Position() { return {x1, x2, y1, x2}; }

// Check collision
bool Box::operator==(const Box &other) {
    if (
        (y1 < other.y1 && y2 > other.y1) ||
        (y1 < other.y2 && y2 > other.y2)
    ) return true;

    return false;
}

Box& Box::operator=(const Box &other) {
    x1 = other.x1;
    x2 = other.x2;
    y1 = other.x1;
    y2 = other.y2;

    return *this;
}

// Move positive
//
// paramaters: {x, y} is the respective distance moving in the coordinate
Box& Box::operator+=(array<int, 2> distance) {
    x1 += distance[0];
    x2 += distance[0];
    y1 += distance[1];
    y2 += distance[1];
}