/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** HealthSystem.cpp
*/

#include "HealthSystem.hpp"

inline void HealthSystem::Update(Coordinator &coordinator)
{
    for (auto entity : this->_entities) {
        auto& hp = coordinator.GetComponent<HealthPoint>(entity);
        if (hp._max_hp != -1) {
            if (hp._curr_hp <= 0) {
                coordinator.AddEvent(Event{Event::actions::DESTROY, entity, {std::any(Velocity{1, 0})}});
                coordinator.DestroyEntity(entity);
                return;
            }
            if (hp._curr_hp >= hp._max_hp) {
                coordinator.AddEvent(Event{Event::actions::MAJ, entity, {std::make_any<int>(entity)}});
                hp._curr_hp = hp._max_hp;
            }
        }
    }
}
