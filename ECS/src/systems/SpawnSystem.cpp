/*
** EPITECH PROJECT, 2023
** RType
** File description:
** SpawnSystem.cpp
*/

#include "systems/SpawnSystem.hpp"
#include <random>

inline void SpawnSystem::Update(Coordinator &coordinator)
{
    // std::cout << "SpawnSystem update :" << std::endl;
    std::random_device rdm;

    rdm();
    for (auto entity : this->_entities) {
        auto& cl = coordinator.GetComponent<SpawnClock>(entity);
        auto& info = coordinator.GetComponent<SpawnInfo>(entity);
        auto& pos = coordinator.GetComponent<Position>(entity);
        cl._spawn_end = std::chrono::steady_clock::now();
        std::uniform_int_distribution<> y((info._y_start), (info._y_end));
        auto elapsed_time = std::chrono::duration_cast<std::chrono::seconds>(cl._spawn_end - cl._spawn_point).count();

        if ((elapsed_time < cl._end) && (elapsed_time != cl._check) && ((elapsed_time % info._seconds) == 0)) {
            cl._check = elapsed_time;
            if (info._shoot != 0)
                coordinator.AddEvent(Event{Event::actions::SPAWN, 0, {y(rdm), pos._x, info._y_vel, info._x, info._y, info.width, info.height, info._hp, info._dmg, info._shoot}});
            else
                coordinator.AddEvent(Event{Event::actions::SPAWN, entity, {(static_cast<int>(pos._y)), pos._x, info._y_vel, info._x, info._y, info.width, info.height, info._hp, info._dmg, info._shoot}});
            return;
        }
        if (elapsed_time > cl._reset) {
            cl._spawn_point = std::chrono::steady_clock::now();
            cl._spawn_end = std::chrono::steady_clock::now();
            cl._check = 0;
            return;
        }
    }
}
