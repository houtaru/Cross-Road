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
        // 
        //  @param
        //  checkForward: True if forward lane and false if backward
        //
        //  @return
        //  False if object goes further than 0 x-coordinate and true otherwise
        virtual bool Move(bool checkForward);

        //  @brief
        //  Render the object
        void Render(SDL_RendererFlip flip=SDL_FLIP_NONE);

        SDL_Rect GetBox() const;
        void SetX(const int &a);

    protected:
        //  The x and y coordinate
        int x, y;

        //  The bounding box
        SDL_Rect box;
};

#endif