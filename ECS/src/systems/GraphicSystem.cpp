/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** GraphicalSystem
*/

#include "components/FlappyHitBox.hpp"
#include "systems/GraphicSystem.hpp"
#include "Graphic.hpp"

inline void GraphicSystem::Update(Coordinator &coordinator)
{
    // std::cout << "GraphicalSystem update :" << std::endl;
    for (auto &entity : this->_entities) {
        auto& pos = coordinator.GetComponent<Position>(entity);
        auto& sprite = coordinator.GetComponent<Sprite>(entity);
        auto& hit = coordinator.GetComponent<Hitbox2>(entity);


        Graphic::drawTextureEx(sprite.texture, {pos._x, pos._y}, 0, sprite.scale, WHITE);
        // Graphic::drawRectangleLines(pos._x + hit._x, pos._y + hit._y, hit.width, hit.height, RED);
    }
}
