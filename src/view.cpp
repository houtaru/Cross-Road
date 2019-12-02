#include "view.hpp"
#include "pointer.hpp"
#include "constants.hpp"
#include "exception.hpp"

#include <memory>
#include <iostream>

using namespace std;

shared_ptr<View> View::instance(nullptr);

shared_ptr<View> View::getInstance() {
    if (instance == nullptr)
        instance = make_shared<View>();
    return instance;
}

View::View():
    colorWhite({0xff, 0xff, 0xff, 0xff}) 
{ 
    cerr << "Constructing view...\n";
}

View::~View() {
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    cerr << "Destructing view...\n";
}

void View::startSDL() {
    try {
        init();
    } catch (const Exception &e) {
        cerr << "Error: " << e.what() << "\n";
    } catch (const char *msg) {
        cerr << "Error: " << msg << "\n";
    }
}

shared_ptr<SDL_Window> View::getWindow() {
    return window;
}

void View::init() {
    initWindow();
    initImage();
    initRenderer();
    initTextureText();
}

void View::initWindow() {
    window = Pointer::createSdlWindow(
        SDL_CreateWindow(
            Constants::GAME_TITLE,
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            Constants::SCREEN_WIDTH,
            Constants::SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN
        )
    );
    if (window == nullptr)
        throw Exception(SDL_GetError());
}

void View::initImage() {
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) && imgFlags))
        throw Exception(IMG_GetError());
}

void View::initRenderer() {
    renderer = Pointer::createSdlRenderer(
        SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED)
    );
    if (renderer == nullptr)
        throw Exception(SDL_GetError());
    SDL_SetRenderDrawBlendMode(renderer.get(), SDL_BLENDMODE_BLEND);
}

void View::initTextureText() {
    if (TTF_Init() == -1)
        throw Exception(TTF_GetError());
}

shared_ptr<SDL_Surface> View::createSurface(const string &path) {
    shared_ptr<SDL_Surface> loadedSurface = Pointer::createSdlSurface(IMG_Load(path.c_str()));
    return loadedSurface;
}

shared_ptr<SDL_Texture> View::createTexture(const string &path) {
    shared_ptr<SDL_Surface> loadedSurface = createSurface(path);
    if (loadedSurface == nullptr)
        throw Exception(IMG_GetError());
    SDL_SetColorKey(loadedSurface.get(), SDL_RLEACCEL, loadedSurface->format->Amask);
    shared_ptr<SDL_Texture> res = Pointer::createSdlTexture(
        SDL_CreateTextureFromSurface(renderer.get(), loadedSurface.get())
    );
    SDL_SetTextureBlendMode(res.get(), SDL_BLENDMODE_BLEND);
    return res;
}

shared_ptr<SDL_Texture> View::createTextureText(const string &text, int fontSize, SDL_Rect *rect, bool isBold) {
    shared_ptr<TTF_Font> font;
    if (isBold) {
        font = Pointer::createTtfFont(
            TTF_OpenFont("assets/fonts/hind-bold.ttf", fontSize)
        );
    } else {
        font = Pointer::createTtfFont(
            TTF_OpenFont("assets/fonts/hind-medium.ttf", fontSize)
        );
    }
    shared_ptr<SDL_Surface> surfaceMessage = Pointer::createSdlSurface(
        TTF_RenderText_Blended(font.get(), text.c_str(), colorWhite)
    );
    *rect = surfaceMessage->clip_rect;
    shared_ptr<SDL_Texture> textureMessage = Pointer::createSdlTexture(
        SDL_CreateTextureFromSurface(renderer.get(), surfaceMessage.get())
    );
    return textureMessage;
}

void View::renderObject(shared_ptr<Object> obj) {
    auto texture = createTexture(obj->path);
    SDL_RenderCopy(renderer.get(), texture.get(), nullptr, &(obj->rect));
    SDL_RenderPresent(renderer.get());
}

void View::renderObject(vector<shared_ptr<Object>> objs) {
    for (auto ptr : objs)
        renderObject(ptr);
}

void View::renderRectObject(shared_ptr<RectObject> obj) {
    auto color = obj->color;
    SDL_SetRenderDrawColor(renderer.get(), color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer.get(), &obj->rect);
    SDL_RenderPresent(renderer.get());
}

void View::renderRectObject(vector<shared_ptr<RectObject>> objs) {
    for (auto ptr : objs)
    renderRectObject(ptr);
}

void View::renderFontObject(shared_ptr<FontObject> obj, int align) {
    int x = obj->rect.x;
    int y = obj->rect.y;
    auto texture = createTextureText(obj->text, obj->fontSize, &obj->rect, obj->isBold);
    obj->rect.x = x;
    obj->rect.y = y;
    if (align == 1) {
        obj->rect.x = x - obj->rect.w / 2;
    } else if (align == 2) {
        obj->rect.x = x - obj->rect.w;
    }
    SDL_RenderCopy(renderer.get(), texture.get(), NULL, &obj->rect);
    obj->rect.x = x;
    obj->rect.y = y;SDL_RenderPresent(renderer.get());
}

void View::renderFontObject(vector<shared_ptr<FontObject>> objs, int align) {
    for (auto ptr : objs)
        renderFontObject(ptr, align);
}