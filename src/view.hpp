#pragma once
#include "object.hpp"
#include "exception.hpp"

#include <memory>
#include <vector>
#include <map>

#ifdef __APPLE__
    #include <SDL.h>
    #include <SDL_image.h>
    #include <SDL_ttf.h>
#else
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
    #include <SDL2/SDL_ttf.h>
#endif

class View {
    public:
        View();
        virtual ~View();

        // return an static instance of View
        static std::shared_ptr<View> getInstance();

        void startSDL();
        
        void renderTexture(std::shared_ptr<Texture> obj);
        void renderTexture(std::vector<std::shared_ptr<Texture>> objs);
        void renderRectObject(std::shared_ptr<RectObject> obj);
        void renderRectObject(std::vector<std::shared_ptr<RectObject>> objs);
        void renderFontObject(std::shared_ptr<FontObject> obj, int align = 0);
        void renderFontObject(std::vector<std::shared_ptr<FontObject>> objs, int align = 0);

        void renderClear();
        void renderPresent();
        
        std::shared_ptr<SDL_Window> getWindow();

    private:
        static std::shared_ptr<View> instance;
        
        std::shared_ptr<SDL_Window> window;
        std::shared_ptr<SDL_Renderer> renderer;

        SDL_Color colorWhite;

        // Initializing things using throughout our project
        void init();
        
        // initialize SDL_Window
        void initWindow();
        
        // initialize SDL_Renderer
        void initRenderer();

        // initialize SDL_image
        void initImage();

        // Initialize TTF_Font
        void initTextureText();

        //  Initialize Texture
        void initTexture();

        //  Create a map of path vs SDL_Texture
        std::map<std::string, std::shared_ptr<SDL_Texture>> storedTexture;

        // create an SDL_Surface from path and wrap it in shared_ptr
        std::shared_ptr<SDL_Surface> createSurface(const std::string &path);
        
        // create an SDL_Texture from path and wrap it in shared_ptr
        std::shared_ptr<SDL_Texture> createTexture(const std::string &path);

        // create an SDL_Texture from a TTF_Font object with the following parameter and wrap it in shared_ptr
        std::shared_ptr<SDL_Texture> createTextureText(const std::string &text, int fontSize, SDL_Rect *rect, bool isBold = false);
};
