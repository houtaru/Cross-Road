#include "view.hpp"
#include "pointer.hpp"
#include "constants.hpp"
#include "exception.hpp"

#include <memory>
#include <iostream>
#include <utility>  //  pair

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
    //cerr << "Constructing view...\n";
}

View::~View() {
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    //cerr << "Destructing view...\n";
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
    initTexture();
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
        SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED)
    );
    if (renderer == nullptr)
        throw Exception(SDL_GetError());
}

void View::initTextureText() {
    if (TTF_Init() == -1)
        throw Exception(TTF_GetError());
}

void View::initTexture() {
    std::vector<std::string> paths;

    //  Add main background
    paths.push_back("assets/images/background/background.png");

    //  Add ground
    paths.push_back("assets/images/ground/ground_01.png");

    //  Add button
    std::vector<std::string> sub;
    Glob(sub, "assets/images/button/*");
    paths.insert(paths.end(), sub.begin(), sub.end());

    //  Add obstacles
    Glob(sub, "assets/images/obstacle/*");
    paths.insert(paths.end(), sub.begin(), sub.end());

    //  Add stuff
    Glob(sub, "assets/images/stuff/*");
    paths.insert(paths.end(), sub.begin(), sub.end());

    //  Add player
    Glob(sub, "assets/images/player/*");
    paths.insert(paths.end(), sub.begin(), sub.end());

    //  Insert to map
    for (auto path : paths)
        storedTexture.insert(std::pair<std::string, std::shared_ptr<SDL_Texture>>(path, createTexture(path)));
}

shared_ptr<SDL_Surface> View::createSurface(const string &path) {
    SDL_Surface *_loadedSurface = IMG_Load(path.c_str());
    if (!_loadedSurface)
        throw Exception(IMG_GetError());
    shared_ptr<SDL_Surface> loadedSurface = Pointer::createSdlSurface(_loadedSurface);
    return loadedSurface;
}

shared_ptr<SDL_Texture> View::createTexture(const string &path) {
    shared_ptr<SDL_Surface> loadedSurface = createSurface(path);
    if (loadedSurface == nullptr)
        throw Exception(IMG_GetError());
    // SDL_SetColorKey(loadedSurface.get(), SDL_RLEACCEL, loadedSurface->format->Amask);
    shared_ptr<SDL_Texture> res = Pointer::createSdlTexture(
        SDL_CreateTextureFromSurface(renderer.get(), loadedSurface.get())
    );
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

void View::renderTexture(shared_ptr<Texture> obj) {
    auto texture = storedTexture.find(obj->path)->second;
    //  Only render textures on the screen
    if (
        obj->rect.x >= -Constants::MAX_LENGHT_OBSTACLE && 
        obj->rect.x <= Constants::SCREEN_WIDTH+Constants::MAX_LENGHT_OBSTACLE
    ) {
        SDL_RenderCopyEx(
            renderer.get(), 
            texture.get(), 
            nullptr, 
            &(obj->rect), 
            0.0, 
            nullptr, 
            obj->flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE
        );
    }
    //if (flag) SDL_RenderPresent(renderer.get());
}

void View::renderTexture(vector<shared_ptr<Texture>> objs) {
    for (auto ptr : objs)
        renderTexture(ptr);
}

void View::renderRectObject(shared_ptr<RectObject> obj) {
    auto color = obj->color;
    SDL_SetRenderDrawColor(renderer.get(), color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer.get(), &obj->rect);
    //SDL_RenderPresent(renderer.get());
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
    //  Center align
    if (align == 1) {
        obj->rect.x = x - obj->rect.w / 2;
    } else if (align == 2) {    //  Left align
        obj->rect.x = x - obj->rect.w;
    }
    SDL_RenderCopy(renderer.get(), texture.get(), NULL, &obj->rect);
    obj->rect.x = x;
    obj->rect.y = y;
    //SDL_RenderPresent(renderer.get());
}

void View::renderFontObject(vector<shared_ptr<FontObject>> objs, int align) {
    for (auto ptr : objs)
        renderFontObject(ptr, align);
}

void View::renderClear() {
    SDL_RenderClear(renderer.get());
}

void View::renderPresent() {
    SDL_RenderPresent(renderer.get());
}