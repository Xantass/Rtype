/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** MovableSystem
*/

#include "systems/MovableSystem.hpp"
#include "Graphic.hpp"
#include <chrono>

inline void MovableSystem::Update(Coordinator &coordinator)
{
    // std::cout << "MovableSystem update :" << std::endl;
    for (auto &entity : this->_entities) {
        //auto& mov = coordinator.GetComponent<Movable>(entity);
        auto& vel = coordinator.GetComponent<Velocity>(entity);
        static std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

        float moveX = 0;
        float moveY = 0;

        if (Graphic::isKeyPressed(KEY_SPACE)) {
            std::chrono::steady_clock::time_point check = std::chrono::steady_clock::now();
            auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(check - start).count();
            if (elapsed_time >= 800) {
                coordinator.AddEvent(Event{Event::actions::SHOOT, 0, {std::any(Velocity{1, 0})}});
                start = std::chrono::steady_clock::now();
            }
        }
        if (Graphic::isKeyDown(KEY_W))
            moveY = -1;
        if (Graphic::isKeyDown(KEY_D))
            moveX = 1;
        if (Graphic::isKeyDown(KEY_S))
            moveY = 1;
        if (Graphic::isKeyDown(KEY_A))
            moveX = -1;
        if (moveX != vel._x || moveY != vel._y) {
            if (moveX != 0 && moveY != 0) {
                moveX *= 0.7;
                moveY *= 0.7;
            }
            coordinator.AddEvent(Event{Event::actions::MOVE, entity, {std::any(Velocity{moveX, moveY})}});
            vel = {moveX, moveY};
        }
    }
}
