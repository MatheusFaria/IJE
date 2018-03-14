#include "game.hpp"
#include "scene.hpp"

#include "gameglobals.hpp"

using namespace engine;

int main(int, char**)
{
    // Configure game
    Game::instance.set_properties(globals::game_name, globals::window_size);

    // Setup scenes
    Scene menu("Main Menu");
    Game::instance.add_scene(menu);

    // Game loop
    Game::instance.run();

    return 0;
}
