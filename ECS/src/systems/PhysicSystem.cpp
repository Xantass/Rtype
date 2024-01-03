/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** PhysicSystem
*/

#include "systems/PhysicSystem.hpp"

void PhysicSystem::Update(Coordinator &coordinator)
{
    for (auto entity : this->_entities) {
        auto& pos = coordinator.GetComponent<Position>(entity);
        auto& vel = coordinator.GetComponent<Velocity>(entity);
        pos._x += vel._x;
        pos._y += vel._y;

    }
}