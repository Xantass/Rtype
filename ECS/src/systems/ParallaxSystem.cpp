/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** ParallaxSystem
*/

#include "systems/ParallaxSystem.hpp"

void ParallaxSystem::Update(Coordinator &coordinator)
{
    std::cout << "ParallaxSystem update :" << std::endl;
    for (auto &entity : this->_entities) {
        auto& pos = coordinator.GetComponent<Position>(entity);
        auto& sprite = coordinator.GetComponent<Sprite>(entity);

        if (pos.x + sprite.texture.width < 0)
            pos.x = 1920;
    }
}
