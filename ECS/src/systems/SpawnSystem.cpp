/*
** EPITECH PROJECT, 2023
** RType
** File description:
** SpawnSystem.cpp
*/

#include "systems/SpawnSystem.hpp"

inline void SpawnSystem::Update(Coordinator &coordinator)
{
    // std::cout << "SpawnSystem update :" << std::endl;
    for (auto entity : this->_entities) {
        auto& cl = coordinator.GetComponent<SpawnClock>(entity);
        cl._spawn_end = std::chrono::high_resolution_clock::now();
        auto elapsed_time = std::chrono::duration_cast<std::chrono::seconds>(cl._spawn_end - cl._spawn_point).count();

        if ((elapsed_time != cl._check) && ((elapsed_time % cl._seconds) == 0)) {
            cl._check = elapsed_time;
            coordinator.AddEvent(Event{Event::actions::SPAWN, 0, {std::any(Velocity{1, 0})}});
        }
    }
}
