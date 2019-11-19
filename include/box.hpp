#ifndef box_hpp
#define box_hpp
#include <utility>
#include <array>

using namespace std;

class Box {
public:
    Box();
    Box(const Box &other);
    ~Box();

    array<int, 4> Position();

    bool operator==(const Box &other);
    Box& operator=(const Box &other);
    Box& operator+=(array<int, 2> distance);

private:
    int x1, x2, y1, y2;
};

#endif