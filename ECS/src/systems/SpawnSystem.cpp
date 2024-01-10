/*
** EPITECH PROJECT, 2023
** RType
** File description:
** SpawnSystem.cpp
*/

#include "systems/SpawnSystem.hpp"
#include <random>

void SpawnSystem::Update(Coordinator &coordinator)
{
    // std::cout << "SpawnSystem update :" << std::endl;
    std::random_device rdm;
    float new_y = 0;

    rdm();
    for (auto entity : this->_entities) {
        auto& cl = coordinator.GetComponent<SpawnClock>(entity);
        auto info = coordinator.GetComponent<SpawnInfo>(entity);
        auto pos = coordinator.GetComponent<Position>(entity);
        cl._spawn_end = std::chrono::high_resolution_clock::now();
        std::uniform_int_distribution<> y((cl._y_start), (cl._y_end));
        auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(cl._spawn_end - cl._spawn_point).count();
        new_y = pos._y;

        if (((elapsed_time / 10) % (cl._seconds / 10)) == 0) {
            if (info._shoot != 0)
                new_y = static_cast<float>(y(rdm));
            coordinator.AddEvent(Event{Event::actions::SPAWN, 0, {std::make_any<float>(new_y), std::make_any<float>(pos._x), std::make_any<float>(info._x_vel), std::make_any<float>(info._hit_w), std::make_any<float>(info._hit_h), std::make_any<int>(info._hp), std::make_any<int>(info._dmg), std::make_any<float>(info._p_end), std::make_any<float>(info._p_vel), std::make_any<int>(info._shoot)}});
            return;
        }
    }
}
