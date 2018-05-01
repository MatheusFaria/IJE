#ifndef __GAME_CODE_MOVE_SIDE_TO_SITE__
#define __GAME_CODE_MOVE_SIDE_TO_SITE__

#include "log.h"

#include "game.hpp"
#include "components/code.hpp"
#include "components/animation_controller.hpp"

class MoveSideToSide : public engine::CodeComponent {
public:
    bool right = true;
    double velocity = 100;

    MoveSideToSide() : engine::CodeComponent() {}

    void update()
    {
        auto dx = velocity * engine::Game::instance.elapsed_time_seconds();
        if (!right) dx *= -1;

        dx = m_game_object->x + dx;

        if (dx >= engine::Game::instance.window_size().first || dx < 0)
        {
            auto animCtrl = m_game_object->get_component<engine::AnimationControllerComponent>();

            right = !right;

            if (!right)
                animCtrl->play_animation("running left");
            else
                animCtrl->play_animation("running right");
        }

        m_game_object->x = dx;
    }

};

#endif
