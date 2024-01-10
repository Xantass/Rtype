/*
** EPITECH PROJECT, 2023
** RType
** File description:
** PathSystem.cpp
*/

#include "systems/PathSystem.hpp"

void PathSystem::Update(Coordinator &coordinator)
{
    for (auto entity : this->_entities) {
        auto& vel = coordinator.GetComponent<Velocity>(entity);
        auto& pos = coordinator.GetComponent<Position>(entity);
        auto& path = coordinator.GetComponent<Path>(entity);
        float diff = path._y_start - pos._y;

        if (diff == 0) {
            vel._y = path._y_vel;
            return;
        }
        if (diff < 0) {
            if ((diff * -1) > path._y_end) {
                vel._y = (path._y_vel * -1);
                return;
            }
        } else {
            if (diff > path._y_end) {
                vel._y = (path._y_vel * -1);
                return;
            }
        }
    }
}
