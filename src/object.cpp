#include "object.hpp"

using namespace std;

Object::Object():
    x(0), y(0), 
    velocity({7, 0})
{
}

Object::Object(string path, SDL_Rect rect, bool _flip):
    x(0), y(0),
    velocity({10, 0}),
    obj(new Texture(path, rect, _flip))
{
}

Object::~Object() {
}

SDL_Rect Object::getBox() const {
    return SDL_Rect({
        x, y + obj->rect.h - Constants::ROCK_HEIGHT,
        obj->rect.w, Constants::ROCK_HEIGHT
    });
}

shared_ptr<Texture> Object::getTexture() const {
    return obj;
}

bool Object::isCollision(std::shared_ptr<Object> &other) {
    SDL_Rect otherBox = other->getBox();
    SDL_Rect box = this->getBox();

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

void Object::setX(int _posX) {
    obj->rect.x = x = _posX;
}

void Object::setY(int _posY) {
    obj->rect.y = y = _posY;
}

bool Object::Move(bool checkForward) {
    if (
        (x <= 0 - obj->rect.w && checkForward) ||
        (x >= Constants::SCREEN_WIDTH + obj->rect.w && !checkForward)
    ) return false;
    else {
        x += (checkForward ? -velocity[0] : velocity[0]);
        obj->rect.x = x;
        return true;
    }
}

// Extra fucntions definition
//
// Load path of all files from `path` in system.
// 
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