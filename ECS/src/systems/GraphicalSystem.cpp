/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** GraphicalSystem
*/

#include "systems/GraphicalSystem.hpp"
#include "Graphic.hpp"
#include "components/HealthPoint.hpp"

inline void GraphicalSystem::Update(Coordinator &coordinator)
{
    // std::cout << "GraphicalSystem update :" << std::endl;
    for (auto &entity : this->_entities) {
        auto& pos = coordinator.GetComponent<Position>(entity);
        auto& sprite = coordinator.GetComponent<Sprite>(entity);
        auto& health = coordinator.GetComponent<HealthPoint>(entity);


        Graphic::drawTextureEx(sprite.texture, {pos._x, pos._y}, 0, sprite.scale, WHITE);
        if (health._max_hp != -1) {
            std::string health_str = std::to_string(health._curr_hp) + "/" + std::to_string(health._max_hp);
            Graphic::drawText(health_str.c_str(), pos._x, pos._y, 20, WHITE);
        }
    }
}
