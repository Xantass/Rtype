/*
** EPITECH PROJECT, 2023
** RType
** File description:
** PathSystem.hpp
*/

#ifndef PATHSYSTEM_HPP_
#define PATHSYSTEM_HPP_

#include "System.hpp"
#include "components/Velocity.hpp"
#include "components/Path.hpp"
#include "components/Position.hpp"

/**
 * @class PathSystem
 * @brief Class of the Path system
 *
 */
class PathSystem : public System {
    public:
        /**
         * @brief Update the path system using the entities stocker in the coordinator
         * @param coordinator : The coordinator of the ECS
         */
        void Update(Coordinator &coordinator);

    protected:
    private:
};

#include "../../src/systems/PathSystem.cpp"

#endif /* !PATHSYSTEM_HPP_ */
