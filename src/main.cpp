#include "game.hpp"

int main() {
    printf("Hello\n");
    try {
        std::shared_ptr<Game> game = Game::GetInstance();
        game->Start();
    } catch(const char* msg) { printf("%s", msg); }

    return 0;
}
