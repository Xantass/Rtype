/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** StaticSystem.cpp
*/

#include "systems/StaticSystem.hpp"

inline void StaticSystem::Update(Coordinator &coordinator)
{
    for (auto entity : this->_entities) {
        auto& vel = coordinator.GetComponent<Velocity>(entity);
        auto& pos = coordinator.GetComponent<Position>(entity);
        auto& stat = coordinator.GetComponent<StaticType>(entity);
        auto& hit = coordinator.GetComponent<Hitbox>(entity);
        float total = 0;
        float mid = 0;
        float offset = 0;

        if (stat._parts != 0)
            total = (hit.height / stat._parts);
        if (pos._x < 1600) {
            vel._x = 0;
            pos._x = 1600;
            for (int i = 0; i < stat._parts; i++) {
                mid = total / 2;
                mid += offset;
                coordinator.AddEvent(Event{Event::actions::SPAWN, 0, {std::make_any<int>(static_cast<int>((mid + pos._y))), std::make_any<float>((pos._x - 20)), std::make_any<float>(0), std::make_any<float>(30), std::make_any<float>(20), std::make_any<float>(100), std::make_any<float>(110), std::make_any<int>(3), std::make_any<int>(1), std::make_any<int>(3)}});
                offset += total;
            }
            break;
        }

    }
}
