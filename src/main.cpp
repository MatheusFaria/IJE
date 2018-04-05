#include "game.hpp"
#include "scene.hpp"
#include "gameobject.hpp"
#include "components/image.hpp"
#include "components/text.hpp"

#include "gameglobals.hpp"

using namespace engine;

int main(int, char**)
{
    // Configure game
    Game::instance.set_properties(globals::game_name, globals::window_size);

    // Setup scenes
    Scene menu("Main Menu");

    auto player = GameObject("Player");
    player.set_position(100, 100);

    auto playerImage = ImageComponent("assets/sprites/image.png");
    player.add_component(playerImage);

    auto title = GameObject("Title");
    title.set_position(250, 250);

    auto title_text = TextComponent("UnB - FGA", "assets/fonts/font.ttf", 30,
                                    Color(0x00, 0x00, 0x00));
    title.add_component(title_text);

    menu.add_game_object(player);
    menu.add_game_object(title);

    Game::instance.add_scene(menu);

    // Game loop
    Game::instance.run();

    return 0;
}
