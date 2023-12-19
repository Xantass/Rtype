/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** PhysicSystem
*/

#include "systems/PhysicSystem.hpp"

void PhysicSystem::Update(Coordinator &coordinator) {
    std::cout << "----------------------" << std::endl << "PhysicSystem update :" << std::endl; // TEST - TO BE REMOVED
    for (auto entity : this->_entities) {
        auto& pos = coordinator.GetComponent<Position>(entity);
        auto& vel = coordinator.GetComponent<Velocity>(entity);
        auto& hitbox = coordinator.GetComponent<Hitbox>(entity);

        for (auto entity2 : this->_entities) {
            if (entity == entity2)
                continue;
            auto& pos2 = coordinator.GetComponent<Position>(entity2);
            auto& hitbox2 = coordinator.GetComponent<Hitbox>(entity2);

            if (pos._x + hitbox._x + hitbox.width >= pos2._x + hitbox2._x &&
                pos._x + hitbox._x <= pos2._x + hitbox2._x + hitbox2.width &&
                pos._y + hitbox._y + hitbox.height >= pos2._y + hitbox2._y &&
                pos._y + hitbox._y <= pos2._y + hitbox2._y + hitbox2.height &&
                hitbox.type == PLAYER && hitbox2.type == PLAYER) {
                std::cout << "Collision with " << entity2 << " detected, idling velocity of entity " << entity << std::endl; // TEST - TO BE REMOVED
                vel._x = 0;
                vel._y = 0;
            }
            if (pos._x + hitbox._x + hitbox.width >= pos2._x + hitbox2._x &&
                pos._x + hitbox._x <= pos2._x + hitbox2._x + hitbox2.width &&
                pos._y + hitbox._y + hitbox.height >= pos2._y + hitbox2._y &&
                pos._y + hitbox._y <= pos2._y + hitbox2._y + hitbox2.height &&
                hitbox.type == PLAYER && hitbox2.type == ENNEMY) {
                std::cout << "Collision with " << entity2 << " detected, destroying entity " << entity << std::endl; // TEST - TO BE REMOVED
                coordinator.DestroyEntity(entity);
                return;
            }
        }

        pos._x += vel._x;
        pos._y += vel._y;

        std::cout << "Entity "<< entity << " position : " << pos._x << " " << pos._y << std::endl; // TEST - TO BE REMOVED
    }
}