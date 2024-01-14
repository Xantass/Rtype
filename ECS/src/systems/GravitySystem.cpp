/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** GraphicalSystem
*/

#include "systems/GravitySystem.hpp"
#include "Graphic.hpp"

inline void GravitySystem::Update(Coordinator &coordinator)
{
    // std::cout << "GraphicalSystem update :" << std::endl;
    for (auto &entity : this->_entities) {
        auto& vel = coordinator.GetComponent<Velocity>(entity);

        if (vel._y != 0)
            vel._y += 0.002;
        if (Graphic::isKeyPressed(KEY_SPACE))
            vel._y = -0.8;
    }
}
