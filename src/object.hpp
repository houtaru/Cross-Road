#ifndef object_hpp
#define object_hpp

#include "texture.hpp"

class Object : public Texture {
    public:
        Object();
        Object(SDL_Renderer *&ren, int xSub=0, int ySub=0);
        virtual ~Object();

        //  @brief
        //  Load texture from file
        //
        //  @param
        //  renderer: The renderer of SDL
        //  path: the local path to file
        void Load(std::string path);

        //  @brief
        //  Polymorphism for player
        //
        //  @param
        //  e: Event from player
        virtual void SetVel(SDL_Event &e);

        //  @brief
        //  Polymorphism for player
        //
        //  @param
        //  stuff: Vector of stuffs to not overlap
        virtual bool Move(std::vector<std::vector<Object*>> &stuff);

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
        //  Render the object
        void Render(SDL_RendererFlip flip=SDL_FLIP_NONE);

        //  @brief
        //  Check whether object collides other object or not
        //
        //  @param:
        //  other: Other object on screen
        bool CheckCollision(Object *&other);

        SDL_Rect GetBox() const;
        void SetX(const int &a);
        void SetY(const int &a);
        void SetW(const int &a);
        
    protected:
        //  The x and y coordinate
        int x, y;

        //  The bounding box
        SDL_Rect box;
};

#endif