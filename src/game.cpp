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
    for (int i = 0; i < 3; ++i) {
        std::vector<Object*> temp;
        stuff.push_back(temp);
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
//  Function like glob.glob() in Python
//
//  @return
//  The vector of path to all files and folders in that folder
//  
//  @param
//  path: The path to specific folder
//
//  @source
//  https://stackoverflow.com/questions/8401777/simple-glob-in-c-on-unix-system
std::vector<std::string> Game::Glob(const std::string &path) {
    using namespace std;

    // glob struct resides on the stack
    glob_t glob_result;
    memset(&glob_result, 0, sizeof(glob_result));

    // do the glob operation
    int return_value = glob(path.c_str(), GLOB_TILDE, NULL, &glob_result);
    if (return_value != 0) {
        globfree(&glob_result);
        stringstream ss;
        ss << "glob() failed with return_value " << return_value << endl;
        throw ss.str(); //std::runtime_error(ss.str());
    }

    // collect all the filenames into a std::list<std::string>
    vector<string> filenames;
    for (size_t i = 0; i < glob_result.gl_pathc; ++i) {
        filenames.push_back(string(glob_result.gl_pathv[i]));
    }

    // cleanup
    globfree(&glob_result);

    // done
    return filenames;
}


//  @brief
//  Check whether new random object's position overlaps other objects' position or not
//
//  @param
//  objects: Vector of objects
//  newObjects: THe new random object
bool Game::CheckOverlap(std::vector<Object*> &objects, Object *&newObject) {
    for (int i = 0; i < objects.size(); ++i) {
        if (newObject == objects[i]) continue;
        if (newObject->CheckCollision(objects[i]))
            return true;
    }
    return false;
}


//  @brief
//  Load textures and sounds from files
void Game::LoadMedia(
    std::string groundPath,
    std::string playerPath,
    std::string obstaclePath,
    std::string stuffPath,
    std::string musicPath,
    std::string diesoundPath
) {
    //  Save the path to dynamic textures
    //std::vector<std::string> animalPath = Glob(obstaclePath + "/animal/*");
    try { this->obstaclePath = Glob(obstaclePath + "/vehicle/*"); }
    catch (std::string error) { throw "Obstacle " + error; }
    this->stuffPath = Glob(stuffPath + "/*");
    //obstaclePath.insert(obstaclePath.end(), animalPath.begin(), animalPath.end());
    //  Load the sounds
    music = Mix_LoadMUS(musicPath.c_str());
    if (!music) throw Mix_GetError();
    diesound = Mix_LoadWAV(diesoundPath.c_str());
    if (!diesound) throw Mix_GetError();

    //  Initialize obstacles for lanes
    int maxObstacle = SCREEN_WIDTH / MAX_LENGHT_OBSTACLE;
    for (int i = LANE1; i <= LANE8; ++i)
        for (int count = 0; count < maxObstacle; ++count) {
            //  Random new type for new object
            int type = rand() % this->obstaclePath.size();

            Object *temp = new Object(renderer, 0, posYlane[i]);
            temp->Load(this->obstaclePath[type]);

            //  Random x-coordinate and check overlap with other objects' position
            do { 
                int pos = rand() % (5*SCREEN_WIDTH);
                pos = ((i % 4) > 1 ? SCREEN_WIDTH-pos : pos);
                //  Set new position
                temp->SetX(pos);
            } while (CheckOverlap(obstacle[i], temp));

            obstacle[i].push_back(temp);
        }

    //  Initialize stuffs
    for (int i = 0; i < stuff.size(); ++i) {
        int maxStuff;
        do {
            maxStuff = rand() % MAX_STUFF;
        } while (maxStuff < MIN_STUFF);
        for (int count = 0; count < maxStuff; ++count) {
            //  Random new type for stuff
            int type = rand() % this->stuffPath.size();

            Object *temp = new Object(renderer, 0, 0);
            temp->Load(this->stuffPath[type]);

            //  Random x-coordinate and check overlap with other objects' position
            do { 
                int posX = rand() % (SCREEN_WIDTH);
                if (posX > SCREEN_WIDTH - temp->GetWidth()) posX -= temp->GetWidth();
                int posY = 0;
                do {
                    posY = rand() % posYcurb[i].second;
                    if (posY > posYcurb[i].second - temp->GetHeight()) posY -= temp->GetHeight();
                } while (posY < posYcurb[i].first);
                //  Set new position
                temp->SetX(posX);
                temp->SetY(posY);
            } while (CheckOverlap(stuff[i], temp));

            temp->SetW(STUFF_WIDTH);
            stuff[i].push_back(temp);
        }
    }

    // Initialize textures
    ground = new Texture(renderer);
    player = new Player(renderer, SCREEN_WIDTH/2, 0);

    //  Load the textures
    ground->Load(groundPath);
    player->Load(playerPath);

    while (CheckOverlap(stuff[0], player)) {
        int posX = rand() % (SCREEN_WIDTH);
        if (posX > SCREEN_WIDTH - player->GetWidth()) posX -= player->GetWidth();
        player->SetX(posX);
    }
    player->SetW(STUFF_WIDTH);
}


//  #brief
//  Thread renders objects
int Game::ThreadRender(int i) {
    for (int j = 0; j < obstacle[i].size(); ++j) {
        //  If the obstacle goes further than 0 x-coordinate
        if (!obstacle[i][j]->Move((i % 4) > 1 ? false : true)) {
            //  Random new type for new object
            int type = rand() % obstaclePath.size();
            obstacle[i][j]->Load(obstaclePath[type]);
            //  Random position for new object until that doesn't overlap other objects' position
            do { 
                int pos = rand() % (4*SCREEN_WIDTH);
                pos = ((i % 4) > 1 ? -pos : pos+SCREEN_WIDTH);
                //  Set new position
                obstacle[i][j]->SetX(pos);
            } while (CheckOverlap(obstacle[i], obstacle[i][j]));

        }
        //  If the object in the screen, render it
        if ((obstacle[i][j]->GetBox().x >= -MAX_LENGHT_OBSTACLE) && (obstacle[i][j]->GetBox().x <= SCREEN_WIDTH+MAX_LENGHT_OBSTACLE))
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
            SDL_PumpEvents();
            //  Handle input for the dot
            player->SetVel(e);
        }

        //  Move the playerc
        player->Move(stuff);

        int threadReturnValue;

        //  Clear screen
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        //  Render background
        ground->Render();
        //  Render stuff
        for (int i = 0; i < stuff.size(); ++i) {
            for (int j = 0; j < stuff[i].size(); ++j)
                stuff[i][j]->Render();
        }

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
