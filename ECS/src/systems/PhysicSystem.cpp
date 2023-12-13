/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** PhysicSystem
*/

#include "systems/PhysicSystem.hpp"

void PhysicSystem::Update(Coordinator &coordinator) {
    std::cout << "PhysicSystem update :" << std::endl; // TEST - TO BE REMOVED
    for (auto entity : this->_entities) {
        auto& pos = coordinator.GetComponent<Position>(entity);
        auto& vel = coordinator.GetComponent<Velocity>(entity);

        pos.x += vel.x;
        pos.y += vel.y;

        std::cout << "Entity position : " << pos.x << " " << pos.y << std::endl; // TEST - TO BE REMOVED
    }
}