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
        static std::shared_ptr<View> GetInstance();

        void StartSDL();
        
        void RenderTexture(std::shared_ptr<Texture> obj);
        void RenderTexture(std::vector<std::shared_ptr<Texture>> objs);
        void RenderRectObject(std::shared_ptr<RectObject> obj);
        void RenderRectObject(std::vector<std::shared_ptr<RectObject>> objs);
        void RenderFontObject(std::shared_ptr<FontObject> obj, int align = 0);
        void RenderFontObject(std::vector<std::shared_ptr<FontObject>> objs, int align = 0);

        void RenderClear();
        void RenderPresent();
        
        std::shared_ptr<SDL_Window> GetWindow();

    private:
        static std::shared_ptr<View> instance;
        
        std::shared_ptr<SDL_Window> window;
        std::shared_ptr<SDL_Renderer> renderer;

        SDL_Color colorWhite;

        //  Initializing things using throughout our project
        void Init();
        //  Initialize SDL_Window
        void InitWindow();
        //  Initialize SDL_Renderer
        void InitRenderer();
        //  Initialize SDL_image
        void InitImage();
        //  Initialize TTF_Font
        void InitTextureText();
        //  Initialize Texture
        void InitTexture();

        //  Create a map of path vs SDL_Texture
        std::map<std::string, std::shared_ptr<SDL_Texture>> storedTexture;

        // create an SDL_Surface from path and wrap it in shared_ptr
        std::shared_ptr<SDL_Surface> CreateSurface(const std::string &path);
        
        // create an SDL_Texture from path and wrap it in shared_ptr
        std::shared_ptr<SDL_Texture> CreateTexture(const std::string &path);

        // create an SDL_Texture from a TTF_Font object with the following parameter and wrap it in shared_ptr
        std::shared_ptr<SDL_Texture> CreateTextureText(const std::string &text, int fontSize, SDL_Rect *rect, bool isBold = false);
};
