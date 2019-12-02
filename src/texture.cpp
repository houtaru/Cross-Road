#include "texture.hpp"

Texture::Texture() {
    renderer = NULL;
    texture = NULL;
    w = h = 0;
}
Texture::Texture(SDL_Renderer *&ren) {
    renderer = ren;
    texture = NULL;
    w = h = 0;
}
Texture::~Texture() { Free(); }

//  @brief  
//
//  Get rid of the existing texture
void Texture::Free() {
    if (texture) {
        SDL_DestroyTexture(texture);
        texture = NULL; 
        w = h = 0;
    }
}

//  Load texture from file
//
//  @param:
//  renderer: The renderer of SDl
//  path: the local path to file
void Texture::Load(std::string path) {
    Free();

    //  Load an image from an specific path
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if (!loadedSurface) throw IMG_GetError();

    //  Color key image
    SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

    //  Create texture from surface pixels
    texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (!texture) throw SDL_GetError();

    //  Get texture size
    w = loadedSurface->w;
    h = loadedSurface->h;

    //  Get rid of loaded surface
    SDL_FreeSurface(loadedSurface);
}   

//  @brief
//  An empty class to access in Object in polymorphism
bool Texture::Move() { return true; }

//  @brief
//  Render texture at given point and given property
//
//  @param
//  x, y: Coordinate
//  clip: A pointer to the source rectangle, or NULL for the entire texture.
//  angle: An angle in degrees that indicates the rotation that will be applied to dstrect, rotating it in a clockwise direction 
//  center: A pointer to a point indicating the point around which dstrect will be rotated (if NULL, rotation will be done around dstrect.w/2, dstrect.h/2).
//  flip: An SDL_RendererFlip value stating which flipping actions should be performed on the texture
void Texture::Render(
    int x, int y,  
    SDL_RendererFlip flip,
    SDL_Rect *clip, 
    double angle, 
    SDL_Point *center
) {
    //  Set rendering space
    SDL_Rect renderQuad = { x, y, w, h, };

    //  Set clip rendering dimension
    if (clip) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //  Render to screen
    SDL_RenderCopyEx(renderer, texture, clip, &renderQuad, angle, center, flip);
}

int Texture::GetWidth() const { return w; }
int Texture::GetHeight() const { return h; }