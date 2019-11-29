#ifndef object_hpp
#define object_hpp

#include "texture.hpp"

class Object : public Texture {
    public:
        Object();
        Object(SDL_Renderer *&ren, int xSub=0, int ySub=0);
        virtual ~Object();

        //  @brief
        //  Move the object
        virtual void Move();

        //  @brief
        //  Render the object
        void Render();

        SDL_Rect GetBox() const;

    protected:
        //  The x and y coordinate
        int x, y;

        //  The bounding box
        SDL_Rect box;
};

#endif