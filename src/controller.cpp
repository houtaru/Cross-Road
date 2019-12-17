#include "controller.hpp"
#include "constants.hpp"
#include "player.hpp"

#include <iostream>
#include <glob.h>
#include <sstream>
#include <fstream>

using namespace std;

// Return an SDL_Rect from `path` which hash upper-left is (_x, _y)
//
SDL_Rect GetRect(string path, int _x = 0, int _y = 0) {
    shared_ptr<SDL_Surface> tmp = Pointer::CreateSdlSurface(IMG_Load(path.c_str()));
    return SDL_Rect({
        _x, _y,
        tmp->w, tmp->h
    });
}

bool CheckOverlap(vector<shared_ptr<Object>> &lane, shared_ptr<Object> &newObject) {
    for (auto obj : lane) 
        if (obj != newObject && newObject->IsCollision(obj)) return true;
    
    return false;
}

// Variables definitions
//
const vector<int> Controller::posY = {
    85, 145, 235, 295, 455, 515, 595, 655, 815+70, 60+875, 60+965,60+1025, 60+1185, 60+1245, 60+1325, 60+1385
};

const vector<pair<int, int>> Controller::posYcurb = {
    {0, 75}, 
    {355, 445}, 
    {715, Constants::SCREEN_HEIGHT}
};

Controller::Controller(int level)
{   
    srand(time(NULL));
    //cerr << "Constructing controller...\n";
    Glob(obstaclePath, "assets/images/obstacle/*");
    Glob(stuffPath, "assets/images/stuff/*");
    lightPath = "assets/images/light/light_01.png";

    //  Initialize obstacles
    int index = 0;
    //  There are 8 lanes
    obstacles.resize(8);
    int maxObstacle = Constants::SCREEN_WIDTH / Constants::MAX_LENGHT_OBSTACLE;
    for (auto &lane : obstacles) {
        for (int i = 0; i < maxObstacle; ++i) {
            //  Random new type for new object
            int type = rand() % this->obstaclePath.size();
            shared_ptr<Object> temp(new Object(
                obstaclePath[type], GetRect(obstaclePath[type], 0, posY[index]), (index % 4) > 1
            ));

            //  Random x-coordinate and check overlap with other objects' position
            do { 
                int pos = rand() % ((8 - level)*Constants::SCREEN_WIDTH/2);
                pos = ((index % 4) > 1 ? Constants::SCREEN_WIDTH - pos : pos);
                //  Set new position
                temp->SetX(pos);
            } while (CheckOverlap(lane, temp));
            lane.push_back(temp); 
        }
        index++;
    }

    //  Initialize parts of light and lights
    //  There are 3 curbs
    stuff.resize(3);
    for (int i = 0; i < 3; ++i) {
        lightParts.push_back(GetRect(lightPath));
        lightParts.back().w /= 3;
        lightParts.back().x = i * lightParts.back().w;
    }
    //  Destination rectangle just has one-third of the original width
    SDL_Rect sub = GetRect(lightPath);
    sub.w /= 3;
    for (int i = 0; i < 4; ++i) {
        lightSigns.push_back(static_cast<SignLight>(rand() % 3));
        lightTimes.push_back(SDL_GetTicks());
        shared_ptr<Object> temp(new Object(
            lightPath, sub, false, lightParts[lightSigns[i]]
        ));

        temp->SetW(Constants::STUFF_WIDTH);
        temp->SetX(i % 2 == 0 ? 5 : (Constants::SCREEN_WIDTH - temp->GetTexture()->rect.w - 5));
        temp->SetY(i % 2 == 0 ? (posY[(i/2)*4] - temp->GetTexture()->rect.h - 10) : (posY[(i/2)*4 + 3] + Constants::VEHICLE_HEIGHT/2) - 15);
        temp->SetH(Constants::ROCK_HEIGHT);

        if (i < 2) 
            stuff[i].push_back(temp);
        else 
            stuff[i-1].push_back(temp);
    }


    //  Initialize other stuffs
    index = 0;
    for (auto &curb : stuff) {
        int maxStuff;
        do {
            maxStuff = rand() % Constants::MAX_STUFF;
        } while (maxStuff < Constants::MIN_STUFF);

        for (int count = 0; count < maxStuff; ++count) {
            int type = rand() % this->stuffPath.size();
            shared_ptr<Object> temp(new Object(
                stuffPath[type], GetRect(stuffPath[type])
            ));

            //  Random x-coordinate and check overlap with other objects' position
            do { 
                int posX = rand() % (Constants::SCREEN_WIDTH);
                if (posX > Constants::SCREEN_WIDTH - temp->GetTexture()->rect.w) posX -= temp->GetTexture()->rect.w;
                int posY = 0;
                do {
                    posY = rand() % posYcurb[index].second;
                    if (posY > posYcurb[index].second - temp->GetTexture()->rect.h) posY -= temp->GetTexture()->rect.h;
                } while (posY < posYcurb[index].first);

                //  Set new position
                temp->SetX(posX);
                temp->SetY(posY);
            } while (CheckOverlap(curb, temp));

            temp->SetW(Constants::STUFF_WIDTH);
            temp->SetH(Constants::ROCK_HEIGHT);
            curb.push_back(temp);
        }
        index++;
    }

    //  Initializer player
    string pathPlayer = "assets/images/player/player_01.png";
    player = make_shared<Player>(
        pathPlayer, GetRect(pathPlayer, Constants::SCREEN_WIDTH/2, 0)
    );
    while (CheckOverlap(stuff[0], player)) {
        int posX = rand() % (Constants::SCREEN_WIDTH);
        if (posX > Constants::SCREEN_WIDTH - player->GetTexture()->rect.x) posX -= player->GetTexture()->rect.x;
        player->SetX(posX);
    }
    player->SetW(Constants::STUFF_WIDTH);

    //cerr << "Constructing controller done!\n";
}

void LoadObject(ifstream &os, std::shared_ptr<Object> &object) {
    //  Read path to object
    std::string path;
    os.ignore(1000, '\n');
    os >> path;
    //  Read bounding box
    SDL_Rect boundingBox;
    os >> boundingBox.x >> boundingBox.y >> boundingBox.w >> boundingBox.h;
    //  Read SDL_Rect
    SDL_Rect _rect;
    os >> _rect.x >> _rect.y >> _rect.w >> _rect.h;
    //  Read flip
    int flip;
    os >> flip;

    object = make_shared<Object>(path, _rect, flip != 0);
    // object->SetX(boundingBox.x);
    // object->SetW(boundingBox.w);
    // object->SetY(boundingBox.y);
    // object->SetH(boundingBox.h);
}

Controller::Controller(bool load, int &level, int &finalScore) {
    srand(time(NULL));
    //cerr << "Constructing controller...\n";
    Glob(obstaclePath, "assets/images/obstacle/*");
    Glob(stuffPath, "assets/images/stuff/*");

    ifstream fin("data/save.txt");

    fin >> level >> finalScore;

    //  Load player
    LoadObject(fin, player);

    //  Load obstacles
    int index = 0;
    //  There are 8 lanes
    obstacles.resize(8);
    for (auto &lane : obstacles) {
        int size;
        fin >> size;
        for (int i = 0; i < size; ++i) {
            std::shared_ptr<Object> temp;
            LoadObject(fin, temp);
            lane.push_back(temp);
        }
        ++index;
    }

    //  Load stuff
    index = 0;
    //  There are 3 curbs
    stuff.resize(3);
    for (auto &lane : stuff) {
        int size;
        fin >> size;
        for (int i = 0; i < size; ++i) {
            std::shared_ptr<Object> temp;
            LoadObject(fin, temp);
            lane.push_back(temp);
        }
    }

    // Load 3 parts of light
    for (int i = 0 ; i < 3; ++i) {
        SDL_Rect temp;
        fin >> temp.x >> temp.y >> temp.w >> temp.h;
        lightParts.push_back(temp);
    }

    //  Load sign of the lights
    for (int i = 0; i < 4; ++i) {
        int temp;
        fin >> temp;
        lightSigns.push_back(static_cast<SignLight>(temp));

        //  Set times for the lights
        lightTimes.push_back(SDL_GetTicks());
    }
    //  Set part for the lights
    stuff[0][0]->SetRectPart(lightParts[lightSigns[0]]);
    stuff[1][0]->SetRectPart(lightParts[lightSigns[1]]);
    stuff[1][1]->SetRectPart(lightParts[lightSigns[2]]);
    stuff[2][0]->SetRectPart(lightParts[lightSigns[3]]);

    fin.close();
    //cerr << "Constructing controller done!\n";
}

Controller::~Controller() {
    //cerr << "Destructing controller...\n";
}

bool Controller::HandlePlayer(SDL_Event &event) {
    while (SDL_PollEvent(&event) != 0) {
        player->SetVel(event);
    }
    player->CanMove(stuff);

    //  If player finishes the current level, return true
    if (player->GetBox().y + player->GetBox().h >= Constants::SCREEN_HEIGHT - 5) return true;
    return false;
}

void Controller::Update(int level) {
    //  Update lights
    for (int i = 0; i < 4; ++i) {
        unsigned int now = SDL_GetTicks();
        if (
            (lightSigns[i] == RED && (now - lightTimes[i] > Constants::RED_DURATION)) ||
            (lightSigns[i] == YELLOW && (now - lightTimes[i] > Constants::YELLOW_DURATION)) ||
            (lightSigns[i] == GREEN && (now - lightTimes[i] > Constants::GREEN_DURATION))
        ) {
            //  Set to next sign
            lightSigns[i] = static_cast<SignLight>((lightSigns[i] + 2) % 3);
            //  Adjust part of texture to render
            switch(i) {
                case 0: stuff[0][0]->SetRectPart(lightParts[lightSigns[i]]); break;
                case 1: stuff[1][0]->SetRectPart(lightParts[lightSigns[i]]); break;
                case 2: stuff[1][1]->SetRectPart(lightParts[lightSigns[i]]); break;
                case 3: stuff[2][0]->SetRectPart(lightParts[lightSigns[i]]); break;
            }
            //  Change time of current sign
            lightTimes[i] = SDL_GetTicks();
        }
    }

    // Update obstacles
    int index = 0;
    for (auto &lane : obstacles) {
        if (lightSigns[index/2] == RED) {
            ++index;
            continue;
        }
        for (int i = 0; i < (int) lane.size(); ++i) {
            //  Slow down obstacle when the light is YELLOW
            if (lightSigns[index/2] == YELLOW)
                lane[i]->SetVel(4);
            else
                lane[i]->SetVel(7);

            if (!lane[i]->Move((index % 4) < 2)) {
                int type = rand() % this->obstaclePath.size();
                lane[i] = make_shared<Object>(
                    obstaclePath[type], GetRect(obstaclePath[type], 0, posY[index]), (index % 4) > 1
                );
                do {
                    int pos = rand() % ((6 - level)*Constants::SCREEN_WIDTH/2);
                    pos = ((index % 4) > 1 ? -pos : pos + Constants::SCREEN_WIDTH);
                    lane[i]->SetX(pos);
                } while (CheckOverlap(lane, lane[i]));
            }
        }
        ++index;
    }
}

void SaveObject(ofstream &os, std::shared_ptr<Object> object) {
    //  Write path to object
    os << object->GetTexture()->path << endl;
    //  Write bounding box
    std::vector<int> boundingBox = object->GetBoundingBox();
    os << boundingBox[0] << " " << boundingBox[1] << " " << boundingBox[2] << " " << boundingBox[3] << endl;
    //  Write SDL_Rect
    SDL_Rect _rect = object->GetTexture()->rect;
    os << _rect.x << " " << _rect.y << " " << _rect.w << " " << _rect.h << endl; 
    //  Write flip
    os << object->GetTexture()->flip << endl;
}

void Controller::Save(int level, int finalScore) {
    //cerr << "Saving..\n";
    ofstream fout("data/save.txt");

    fout << level << " " << finalScore << endl;

    //  Write info of player
    SaveObject(fout, player);

    //  Write info of obstacles
    for (auto lane : obstacles) {
        fout << lane.size() << endl;
        for (int i = 0; i < lane.size(); ++i)
            SaveObject(fout, lane[i]);
    }

    //  Write info of stuffs
    for (auto lane : stuff) {
        fout << lane.size() << endl;
        for (int i = 0; i < lane.size(); ++i)
            SaveObject(fout, lane[i]);
    }
    
    //  Write 3 parts of light
    for (auto part : lightParts)
        fout << part.x << " " << part.y << " " << part.w << " " << part.h << endl;

    //  Write time of lights
    for (auto sign : lightSigns)
        fout << sign << " ";

    fout.close();
}

bool Controller::CheckCollision() {
    for (auto &lane: obstacles) {
        for (int i = 0; i < (int) lane.size(); ++i) {
            if (player->IsCollision(lane[i])) return true;
        }
    }
    return false;
}

std::vector<std::shared_ptr<Texture>> Controller::GetObstacles() {
    std::vector<std::shared_ptr<Texture>> res;
    for (auto lane : obstacles)
        for (auto it : lane) res.push_back(it->GetTexture());
    return res;
}

std::vector<std::shared_ptr<Texture>> Controller::GetStuff() {
    std::vector<std::shared_ptr<Texture>> res;
    for (auto lane : stuff)
        for (auto it : lane) res.push_back(it->GetTexture());
    return res;
}

std::shared_ptr<Texture> Controller::GetPlayer() {
    return player->GetTexture();
}
