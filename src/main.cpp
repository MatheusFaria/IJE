#include "game.hpp"
#include "scene.hpp"
#include "gameobject.hpp"
#include "components/image.hpp"
#include "components/text.hpp"
#include "components/animation.hpp"
#include "components/animation_controller.hpp"
#include "components/audio.hpp"

#include "gameglobals.hpp"
#include "movesidetoside.hpp"
#include "move.hpp"

using namespace engine;

int main(int, char**)
{
    // Configure game
    Game::instance.set_properties(globals::game_name, globals::window_size);

    // Setup scenes
    Scene menu("Main Menu");

    auto player = GameObject("Player", 1, 0);
    player.set_position(0, 0);

    auto playerImage = ImageComponent("image.png");
    player.add_component(playerImage);

    auto title = GameObject("Title", 1, 0);
    title.set_position(10, 10);

    auto title_text = TextComponent("UnB - FGA", "font.ttf", 30,
                                    Color(0x00, 0x00, 0x00));

    auto bg_music = AudioComponent("music.ogg", true);

    title.add_component(title_text);
    title.add_component(bg_music);

    Move move;
    title.add_component(move);

    player.set_parent(title);

    GameObject boy("Boy", 0, 0);
    boy.set_position(10, 10);

    AnimationControllerComponent animCtrl;

    AnimationComponent boyAnimation("boy.png", 8, 2, 1.0, true);
    boyAnimation.set_end_frame(7);
    animCtrl.add_animation("running right", boyAnimation);

    AnimationComponent boyAnimation2("boy.png", 8, 2, 1.0, true);
    boyAnimation2.set_frame_range(8, 15);
    animCtrl.add_animation("running left", boyAnimation2);

    MoveSideToSide movesidetoside;

    boy.add_component(movesidetoside);
    boy.add_component(boyAnimation);
    boy.add_component(boyAnimation2);
    boy.add_component(animCtrl);


    menu.add_game_object(player);
    menu.add_game_object(title);
    menu.add_game_object(boy);

    Game::instance.add_scene(menu);

    // Game loop
    Game::instance.run();

    return 0;
}
