#ifndef texture_hpp
#define texture_hpp

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <string>
#include "constant.hpp"

class Texture {
    public:
        Texture();
        Texture(SDL_Renderer *&ren);
        virtual ~Texture();

        // Get rid of the exissting texture
        void Free();

        //  @brief
        //  Load texture from file
        //
        //  @param
        //  renderer: The renderer of SDL
        //  path: the local path to file
        void Load(std::string path);

        //  @brief
        //  Render texture at given point and given property
        //
        //  @param
        //  x, y: Coordinate
        //  clip: A pointer to the source rectangle, or NULL for the entire texture.
        //  angle: An angle in degrees that indicates the rotation that will be applied to dstrect, rotating it in a clockwise direction 
        //  center: A pointer to a point indicating the point around which dstrect will be rotated (if NULL, rotation will be done around dstrect.w/2, dstrect.h/2).
        //  flip: An SDL_RendererFlip value stating which flipping actions should be performed on the texture
        virtual void Render(
            int x=0, int y=0, 
            SDL_Rect *clip=NULL, 
            double angle=0.0, 
            SDL_Point *center=NULL, 
            SDL_RendererFlip flip=SDL_FLIP_NONE
        );

        int GetWidth() const;
        int GetHeight() const;

    protected:
        //  The renderer of SDL
        SDL_Renderer *renderer;

        //  The actual hardware texture
        SDL_Texture *texture;

        //  Width and height of the texture
        int w, h;
};


#endif