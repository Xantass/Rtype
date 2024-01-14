/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** ControlSystem.cpp
*/

#include "systems/ControlSystem.hpp"

inline void ControlSystem::Update(Coordinator &coordinator)
{
    // std::cout << "ControlSystem update :" << std::endl;
    for (auto entity : this->_entities) {
        auto& con = coordinator.GetComponent<Controllable>(entity);
        auto& pos = coordinator.GetComponent<Position>(entity);
        if (con.type == PLAYER_INPUT) {
            // std::cout << "Player in control" << std::endl;
        } else if (con.type == IA) {
            if (pos._x < -200) {
                coordinator.AddEvent(Event{Event::actions::DESTROY, entity, {std::any(Velocity{1, 0})}});
                return;
            }
        } else {
            if (pos._x > 2000 || pos._x < -200) {
                coordinator.AddEvent(Event{Event::actions::DESTROY, entity, {std::any(Velocity{1, 0})}});
                return;
            }
        }
    }
}
