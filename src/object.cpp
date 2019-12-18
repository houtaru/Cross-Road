#include "object.hpp"

using namespace std;

Object::Object():
    x(0), y(0), w(0), h(0),
    velocity({7, 0})
{}

Object::Object(string path, SDL_Rect rect, bool _flip, SDL_Rect rect_part):
    x(rect.x), y(rect.y + rect.h-Constants::OBJECT_HEIGHT), 
    w(rect.w), h(Constants::OBJECT_HEIGHT),
    velocity({7, 0}),
    obj(new Texture(path, rect, _flip, rect_part))
{}

Object::~Object() {}

SDL_Rect Object::GetBox() const { return SDL_Rect({x, y, w, h}); }

shared_ptr<Texture> Object::GetTexture() const { return obj; }
std::vector<int> Object::GetBoundingBox() const {
    std::vector<int> res;
    res.push_back(x);
    res.push_back(y);
    res.push_back(w);
    res.push_back(h);
    return res;
}

void Object::SetX(int _posX) {
    obj->rect.x = x = _posX;
}

void Object::SetY(int _posY) {
    obj->rect.y = _posY;
    y = _posY + (obj->rect.h - Constants::OBJECT_HEIGHT);
}

void Object::SetW(int _w) {
    w = _w;
    x = obj->rect.x + (obj->rect.w - w)/2;
}

void Object::SetH(int _h) {
    h = _h;
    y = obj->rect.y + (obj->rect.h - h);
}

void Object::SetRectPart(SDL_Rect _rect_part) {
    obj->rect_part = _rect_part;
}

bool Object::IsCollision(std::shared_ptr<Object> &other) {
    SDL_Rect otherBox = other->GetBox();
    SDL_Rect box = this->GetBox();

    //  The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //  Calculate the sides of rect A
    leftA = box.x;
    rightA = box.x + box.w;
    topA = box.y;
    bottomA = box.y + box.h;

    //  Calculate the sides of rect B
    leftB = otherBox.x;
    rightB = otherBox.x + otherBox.w;
    topB = otherBox.y;
    bottomB = otherBox.y + otherBox.h;

	//If any of the sides from A are outside of B
    if(bottomA <= topB) return false;
    if(topA >= bottomB) return false;
    if(rightA <= leftB) return false;
    if(leftA >= rightB) return false;

    //  If none of the sides from A are outside B
    return true;
}

bool Object::Move(bool checkForward) {
    if (
        (obj->rect.x <= 0 - obj->rect.w && checkForward) ||
        (obj->rect.x >= Constants::SCREEN_WIDTH + obj->rect.w && !checkForward)
    ) return false;
    else {
        obj->rect.x += (checkForward ? -velocity[0] : velocity[0]);
        x = obj->rect.x;
        return true;
    }
}

void Object::SetVel(const int &vel) {
    velocity[0] = vel;
}

void Object::SetVel(SDL_Event &event) {}
void Object::CanMove(std::vector<std::vector<std::shared_ptr<Object>>> &stuff) {}


//  ------------------------------
void Glob(vector<string> &list, string path) {
    // glob struct resides on the stack
    glob_t glob_result;
    memset(&glob_result, 0, sizeof(glob_result));

    // do the glob operation
    int return_value = glob(path.c_str(), GLOB_TILDE, NULL, &glob_result);
    if (return_value != 0) {
        globfree(&glob_result);
        stringstream ss;
        ss << "glob() failed with return_value " << return_value << endl;
        throw "+ " + ss.str(); //std::runtime_error(ss.str());
    }

    // collect all the filenames into a std::list<std::string>
    list.clear();
    for (size_t i = 0; i < glob_result.gl_pathc; ++i) {
        list.push_back(string(glob_result.gl_pathv[i]));
    }

    // cleanup
    globfree(&glob_result);
}