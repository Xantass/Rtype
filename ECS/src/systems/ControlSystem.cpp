/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** ControlSystem.cpp
*/

#include "systems/ControlSystem.hpp"

void ControlSystem::Update(Coordinator &coordinator)
{
    // std::cout << "ControlSystem update :" << std::endl;
    for (auto entity : this->_entities) {
        auto& con = coordinator.GetComponent<Controllable>(entity);
        auto& pos = coordinator.GetComponent<Position>(entity);
        auto& vel = coordinator.GetComponent<Velocity>(entity);
        if (con.type == INPUT) {
            std::cout << "Player in control" << std::endl;
        } else if (con.type == IA) {
            std::cout << "IA in control" << std::endl;
        } else {
            if (pos._x > 2000) {
                std::cout << "Destroyed entity : " << entity << std::endl;
                coordinator.DestroyEntity(entity);
                std::cout << "All done" << std::endl;
                return;
            }
        }
    }
}