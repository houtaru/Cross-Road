#include "game.hpp"


Game::Game() {
    //  Initialize random seed
    srand(time(NULL));

    window = NULL;
    renderer = NULL;
    ground = NULL;
    player = NULL;
    music = NULL;
    diesound = NULL;
    for (int i = LANE1; i <= LANE8; ++i) {
        std::vector<Object*> temp;
        obstacle.push_back(temp);
    }

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

    //  Free objects of lanes
    for (int i = LANE1; i <= LANE8; ++i)
        for (int j = obstacle[i].size()-1; j >= 0; --j) delete obstacle[i][j];

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


//  @brief
//
//  Check whether new random object's position overlaps other objects' position or not
bool Game::CheckOverlap(const std::vector<Object*> &lane, int random) {
    for (int i = 0; i < lane.size(); ++i) {
        SDL_Rect box = lane[i]->GetBox();
        if ((random >= box.x && random <= box.x+box.w+10) ||
            (random+146 >= box.x && random+146 <= box.x+box.w+10)
        ) return true;
    }
    return false;
}


//  @brief
//  Load textures and sounds from files
void Game::LoadMedia(
    std::string groundPath,
    std::string playerPath,
    std::string carPath,
    std::string truckPath,
    std::string musicPath,
    std::string diesoundPath
) {
    // Initialize textures
    ground = new Texture(renderer);
    player = new Player(renderer, SCREEN_WIDTH/2, 0);

    //  Load the textures
    ground->Load(groundPath);
    player->Load(playerPath);

    //  Save the path to dynamic textures
    this->truckPath = truckPath;
    this->carPath = carPath;

    //  Load the sounds
    music = Mix_LoadMUS(musicPath.c_str());
    if (!music) throw Mix_GetError();
    diesound = Mix_LoadWAV(diesoundPath.c_str());
    if (!diesound) throw Mix_GetError();

    //  Initialize objects for lanes
    int maxObject = SCREEN_WIDTH / 250;
    for( int i = LANE1; i <= LANE8; ++i)
        for (int count = 0; count < maxObject; ++count) {
            int type = rand() % 2;

            Object *temp = new Object(renderer, 0, posY[i]);
            switch(type) {
                case TRUCK: temp->Load(truckPath); break;
                case CAR: temp->Load(carPath); break;
                default: break;
            }

            //  Random x-coordinate and check overlap with other objects' position
            int pos;
            do { 
                //printf("1\n");
                pos = rand() % (5*SCREEN_WIDTH);
                pos = ((i % 4) > 1 ? SCREEN_WIDTH-pos : pos);
            } while (CheckOverlap(obstacle[i], pos));
            temp->SetX(pos);

            obstacle[i].push_back(temp);
        }
}


//  #brief
//  Thread renders objects
int Game::ThreadRender(int i) {
    for (int j = 0; j < obstacle[i].size(); ++j) {
        //  If the obstacle goes further than 0 x-coordinate
        if (!obstacle[i][j]->Move((i % 4) > 1 ? false : true)) {
            //  Random position for new object until that doesn't overlap other objects' position
            int pos = 0;
            do { 
                pos = rand() % (4*SCREEN_WIDTH);
                pos = ((i % 4) > 1 ? -pos : pos+SCREEN_WIDTH);
            } while (CheckOverlap(obstacle[i], pos));

            //  Set new position
            obstacle[i][j]->SetX(pos);
        }
        //  If the object in the screen, render it
        if ((obstacle[i][j]->GetBox().x >= -200) && (obstacle[i][j]->GetBox().x <= SCREEN_WIDTH+200))
            obstacle[i][j]->Render((i % 4) > 1 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
    }

    return 0;
}


//  #brief
//  Thread checks collision
int Game::ThreadCheckCollision(int i) {
    for (int j = 0; j < obstacle[i].size(); ++j)
        if (player->CheckCollision(obstacle[i][j])) {
            //  Stop music theme
            Mix_HaltMusic();
            //  Play die sound effect
            Mix_PlayChannel(-1, diesound, 0);
            //  Delay screen for playing sound effect
            SDL_Delay(3000);
            return 1;
        }

    return 0;
}


//  @brief
//  Run game
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

        int threadReturnValue;

        //  Clear screen
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        //  Render background
        ground->Render();

        //  Render objects
        for (int i = LANE1; i <= LANE8; ++i) {
            std::thread temp(&Game::ThreadRender, this, i);
            if (temp.joinable())
                temp.join();
        }

    
        //  Render player
        player->Object::Render();

        //  Check collision of player
        for (int i = LANE1; i <= LANE8; ++i) {
            std::future<int> temp = std::async(std::launch::async, &Game::ThreadCheckCollision, this, i);
            int stopSignal = temp.get();
            //  If there is a collision, stop the Run function
            if (stopSignal == 1) return;
        }

        //Update screen
        SDL_RenderPresent(renderer);

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) SDL_Delay(frameDelay - frameTime);
    }
}
