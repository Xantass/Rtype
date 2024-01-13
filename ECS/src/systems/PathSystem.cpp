/*
** EPITECH PROJECT, 2023
** RType
** File description:
** PathSystem.cpp
*/

#include "systems/PathSystem.hpp"

inline void PathSystem::Update(Coordinator &coordinator)
{
    for (auto entity : this->_entities) {
        auto& vel = coordinator.GetComponent<Velocity>(entity);
        auto& pos = coordinator.GetComponent<Position>(entity);
        auto& path = coordinator.GetComponent<Path>(entity);

        std::vector<Position> pathToFollow = {
            {1500, 200},
            {1400, 500},
            {1100, 300},
            {800, 10}
        };

        if (path._currentAim >= pathToFollow.size()) {
            vel._x = -5;
            vel._y = 0;
            continue;
        }

        float xToReach = pathToFollow[path._currentAim]._x;
        float yToReach = pathToFollow[path._currentAim]._y;

        if (pos._x < xToReach)
            vel._x = 5;
        else if (pos._x > xToReach)
            vel._x = -5;
        else
            vel._x = 0;
        
        if (pos._y < yToReach)
            vel._y = 5;
        else if (pos._y > yToReach)
            vel._y = -5;
        else
            vel._y = 0;

        if (fmod(pos._x, xToReach) <= 10 && fmod(pos._y, yToReach) <= 10) {
            path._currentAim++;
        }
    }
}
