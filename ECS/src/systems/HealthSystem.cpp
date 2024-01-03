/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** HealthSystem.cpp
*/

#include "HealthSystem.hpp"

void HealthSystem::Update(Coordinator &coordinator)
{
    for (auto entity : this->_entities) {
        auto& hp = coordinator.GetComponent<HealthPoint>(entity);
        if (hp._curr_hp <= 0) {
            //Destroy Entity
            std::cout << entity << " has 0 hp remaining" << std::endl;
        }
    }
}
