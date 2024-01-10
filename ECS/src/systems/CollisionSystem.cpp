/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** CollisionSystem.cpp
*/

#include "systems/CollisionSystem.hpp"

inline void CollisionSystem::Update(Coordinator &coordinator)
{
    for (auto entity : this->_entities) {
        auto& pos = coordinator.GetComponent<Position>(entity);
        auto& hit = coordinator.GetComponent<Hitbox>(entity);
        for (auto comp : this->_entities) {
            if (entity == comp)
                continue;
            auto& c_pos = coordinator.GetComponent<Position>(comp);
            auto& c_hit = coordinator.GetComponent<Hitbox>(comp);
            if (pos._x + hit._x + hit.width >= c_pos._x + c_hit._x &&
                pos._x + hit._x <= c_pos._x + c_hit._x + c_hit.width &&
                pos._y + hit._y + hit.height >= c_pos._y + c_hit._y &&
                pos._y + hit._y <= c_pos._y + c_hit._y + c_hit.height) {
                if ((hit.type == PLAYER && c_hit.type == PLAYER) || (hit.type == PLAYER && c_hit.type == BULLET) || (hit.type == BULLET && c_hit.type == PLAYER))
                    break;
                auto& dmg = coordinator.GetComponent<Damage>(entity);
                auto& hp = coordinator.GetComponent<HealthPoint>(entity);
                auto& c_dmg = coordinator.GetComponent<Damage>(comp);
                auto& c_hp = coordinator.GetComponent<HealthPoint>(comp);
                hp._curr_hp -= c_dmg._curr_dmg;
                c_hp._curr_hp -= dmg._curr_dmg;
                return;
            }
        }
    }
}
