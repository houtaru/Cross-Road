#include "game.hpp"


Game::Game() {
    window = NULL;
    renderer = NULL;
    ground = NULL;
    car = NULL;
    truck = NULL;
    player = NULL;
    music = NULL;
    diesound = NULL;

	//  Initialize SDl
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) throw SDL_GetError();

    //  Set texture filtering to linear
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) 
        throw "Warning: Linear texture filtering not enabled!";

    //  Create window
    window = SDL_CreateWindow(
        "Cross Road",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );
    if (!window) throw SDL_GetError();

    //  Create vsynced renderer for window
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) throw SDL_GetError();

    //  Initialize renderer color
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    //  Initialize PND loading
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) throw IMG_GetError();

    //  Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) throw Mix_GetError();

    // Initialize textures
    ground = new Texture(renderer);
    player = new Player(renderer, SCREEN_WIDTH/2, 0);
    car = new Object(renderer, SCREEN_WIDTH, 295);
    truck = new Object(renderer, SCREEN_WIDTH+10, 235);
}
Game::~Game() {
    //  Destroy window
    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    //  Destroy renderer
    SDL_DestroyWindow(window);
    window = NULL;

    //  Deallocate memory
    delete ground;
    delete player;
    delete car;
    delete truck;

    // Free sound
    Mix_FreeMusic(music);
    music = NULL;
    Mix_FreeChunk(diesound);
    diesound = NULL;

    //  Quit subsystem
    Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}


void Game::LoadMedia(
    std::string groundPath,
    std::string playerPath,
    std::string carPath,
    std::string truckPath,
    std::string musicPath,
    std::string diesoundPath
) {
    //  Load the textures
    ground->Load(groundPath);
    player->Load(playerPath);
    car->Load(carPath);
    truck->Load(truckPath);

    //  Load the sounds
    music = Mix_LoadMUS(musicPath.c_str());
    if (!music) throw "Unable to load music " + musicPath + "! Mix Error: " + Mix_GetError();
    diesound = Mix_LoadWAV(diesoundPath.c_str());
    if (!diesound) throw "Unable to load die sound " + diesoundPath + "! Mix_image Error: " + Mix_GetError();
}


void Game::Run() {
    //  Limit  FPS
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    Uint32 frameStart;
    int frameTime;

    //  Main loop flag
    bool quit = false;

    //  Play music theme
    Mix_PlayMusic(music, -1);

    //  Event handler
    SDL_Event e;

    //  While application is running
    while (!quit) {
        frameStart = SDL_GetTicks();

        //  Handle events on queue
        while(SDL_PollEvent(&e) != 0) {
            //  User requests quit
            if (e.type == SDL_QUIT) quit = true;

            //  Handle input for the dot
            player->SetVel(e);
        }

        //  Move the player
        player->Move();

        //  Clear screen
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        //  Render background
        ground->Render();
        //  Render objects
        car->Move();
        car->Render();
        truck->Move();
        truck->Render();
        //  Render player
        player->Object::Render();
        if (player->CheckCollision(car) || player->CheckCollision(truck)) {
            //Stop music theme;
            Mix_HaltMusic();
            //Play die sound effect;
            Mix_PlayChannel(-1, diesound, 0);
            //Delay screen for playing sound effect;
            SDL_Delay(3000);
            break;
        }

        //Update screen
        SDL_RenderPresent(renderer);

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) SDL_Delay(frameDelay - frameTime);
    }
}
