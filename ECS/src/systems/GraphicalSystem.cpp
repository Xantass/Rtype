/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** GraphicalSystem
*/

#include "systems/GraphicalSystem.hpp"
#include "Graphic.hpp"

inline void GraphicalSystem::Update(Coordinator &coordinator)
{
    // std::cout << "GraphicalSystem update :" << std::endl;
    for (auto &entity : this->_entities) {
        auto& pos = coordinator.GetComponent<Position>(entity);
        auto& sprite = coordinator.GetComponent<Sprite>(entity);

        Graphic::drawTexture(sprite.texture, pos._x, pos._y, WHITE);
    }
}
