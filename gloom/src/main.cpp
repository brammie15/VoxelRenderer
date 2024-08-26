// Local headers
#include "gloom/config.hpp"
#include "Game.h"

// Standard headers
#include <cstdlib>





int main(int argc, char *argb[]) {
    srand(time(nullptr));
    std::cout << "Seed: " << SEED << std::endl;
    Game game;
    game.run();

    return EXIT_SUCCESS;
}
