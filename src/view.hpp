#pragma once
#include "exception.hpp"
#include "object.hpp"

#include <memory>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class View {
    public:
        View();
        virtual ~View();

        static std::shared_ptr<View> getInstance();

        void startSDL();
        
        void renderObject(std::shared_ptr<Object> obj);
        void renderObject(std::vector<std::shared_ptr<Object>> objs);
        void renderRectObject(std::shared_ptr<RectObject> obj);
        void renderRectObject(std::vector<std::shared_ptr<RectObject>> objs);
        void renderFontObject(std::shared_ptr<FontObject> obj, int align = 0);
        void renderFontObject(std::vector<std::shared_ptr<FontObject>> objs, int align = 0);
        
        shared_ptr<SDL_Window> getWindow();

    private:
        static std::shared_ptr<View> instance;
        
        std::shared_ptr<SDL_Window> window;
        std::shared_ptr<SDL_Renderer> renderer;

        SDL_Color colorWhite;

        void init();
        void initWindow();
        void initRenderer();
        void initImage();
        void initTextureText();

        shared_ptr<SDL_Surface> createSurface(const string &path);
        shared_ptr<SDL_Texture> createTexture(const string &path);
        shared_ptr<SDL_Texture> createTextureText(const string &text, int fontSize, SDL_Rect *rect, bool isBold = false);
};
