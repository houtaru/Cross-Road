#pragma once

#include "constants.hpp"

#include <string>
#include <memory>
#include <vector>
#include <functional>
#include <sstream>
#include <glob.h>

#ifdef __APPLE__
    #include <SDL.h>
    #include <SDL_image.h>
    #include <SDL_ttf.h>
    #include <SDL_mixer.h>
#else
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
    #include <SDL2/SDL_ttf.h>
    #include <SDL2/SDL_mixer.h>
#endif

// An object can be render to screen
// Variables:
//      - string path: path to image.
//      - SDL_Rect rect: position on the screen when it is displayed.
//
struct Texture {
    std::string path;
    SDL_Rect rect;
    SDL_Rect rect_part;
    bool flip;
    Texture(std::string _path, const SDL_Rect &_rect, bool _flip=false, const SDL_Rect &_rect_part={0, 0, 0, 0}): 
        path(_path), rect(_rect), flip(_flip), rect_part(_rect_part) {}
};

// A rectangle object contains a single color that can be render to screen.
// Variables:
//      - SDL_Rect rect: position on the screen when it is displayed.
//      - SDL_Color color: color of rectangle object
// 
struct RectObject {
    SDL_Rect rect;
    SDL_Color color;
    RectObject(const SDL_Rect &_rect, const SDL_Color &_color): rect(_rect), color(_color) {}
};

// A font object can be render to screen.
// Variables:
//      - string text: the text will be displayed to screen.
//      - int fontSize: size of text when it is displayed on screen.
//      - SDL_Rect rect: position on the screen when it is displayed.
//      - bool isBold: is it bold or not.
//
struct FontObject {
    std::string text;
    int fontSize;
    SDL_Rect rect;
    bool isBold;
    FontObject(std::string _text, const SDL_Rect &_rect): text(_text), fontSize(24), rect(_rect), isBold(false) {}
    FontObject(std::string _text, int _fontSize, const SDL_Rect &_rect):
        text(_text), fontSize(_fontSize), rect(_rect), isBold(false) {}
    FontObject(std::string _text, int _fontSize, const SDL_Rect &_rect, bool _isBold):
        text(_text), fontSize(_fontSize), rect(_rect), isBold(_isBold) {}
};

// Button object
// Variables:
//      - Texture* obj: graphic of button.
//      - void callback(): run when user click the button.
//
struct Button {
    std::shared_ptr<Texture> obj;
    std::function<void()> callback;

    Button(): obj(), callback() {}
    Button(std::shared_ptr<Texture> _obj, std::function<void()> _callback):
        obj(_obj), callback(_callback) {}
};

class Object {
    public:
        Object();
        Object(std::string path, SDL_Rect rect, bool _flip=false, SDL_Rect rect_part={0, 0, 0, 0});
        virtual ~Object();

        SDL_Rect getBox() const;

        std::shared_ptr<Texture> getTexture() const;
        
        void setX(int _posX);
        void setY(int _posY);
        void setW(int _w);
        void setH(int _h);
        
        //  @brief
        //  Set rectangle for rendering a part of texture
        void setRectPart(SDL_Rect _rect_part);

        //  @brief
        //  Check whether object collides other object or not
        //
        //  @param:
        //  other: Other object on screen
        //
        bool isCollision(std::shared_ptr<Object> &other);

        //  @brief
        //  Move the object
        // 
        //  @param
        //  checkForward: True if forward lane and false if backward
        //
        //  @return
        //  False if object goes further than 0 x-coordinate and true otherwise
        bool Move(bool checkForward);

        //  @brief
        //  Adjust velocity of obstacle
        //
        //  @param
        //  vel: New velocity
        void setVel(const int& vel);

        //  Function for polymorphism in Player class
        virtual void setVel(SDL_Event &event);
        //  Function for polymorphism in Player class
        virtual void canMove(std::vector<std::vector<std::shared_ptr<Object>>> &stuff);

    protected:
        std::vector<int> velocity; // 0/1: X/Y velocity

        int x, y, w, h;
        std::shared_ptr<Texture> obj;
};

//  ------------------------------


//  @brief
//  Function like glob.glob() in Python
//  
//  @param
//  list: vector of string you want to save paths into
//  path: The path to specific folder
//
//  @source
//  https://stackoverflow.com/questions/8401777/simple-glob-in-c-on-unix-system
void Glob(std::vector<std::string> &list, std::string path);