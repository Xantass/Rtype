/*
** EPITECH PROJECT, 2023
** RType
** File description:
** SpawnSystem.hpp
*/

#ifndef SPAWNSYSTEM_HPP_
#define SPAWNSYSTEM_HPP_

#include "../Coordinator.hpp"
#include "../System.hpp"
#include "../components/SpawnClock.hpp"
#include "../components/SpawnInfo.hpp"
#include "../components/Position.hpp"

/**
 * @class SpawnSystem
 * @brief Class of the Spawn system
 *
 */
class SpawnSystem : public System {
    public:
        /**
         * @brief Update the Spawn system using the entities stocker in the coordinator
         * @param coordinator : The coordinator of the ECS
         */
        void Update(Coordinator &coordinator);

    protected:
    private:
};

#include "../../src/systems/SpawnSystem.cpp"

#endif /* !SPAWNSYSTEM_HPP_ */
