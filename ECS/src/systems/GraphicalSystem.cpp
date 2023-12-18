/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** GraphicalSystem
*/

#include "../../inc/systems/GraphicalSystem.hpp"

void GraphicalSystem::Update(Coordinator &coordinator)
{
    std::cout << "GraphicalSystem update :" << std::endl;
    for (auto &entity : this->_entities) {
        auto& pos = coordinator.GetComponent<Position>(entity);
        auto& sprite = coordinator.GetComponent<Sprite>(entity);

        DrawTexture(sprite.texture, pos.x, pos.y, RAYWHITE);
    }
}
