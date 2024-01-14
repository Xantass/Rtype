/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** StaticSystem.hpp
*/

/**
 * @file StaticSystem.hpp
 * @brief File containing the Static system
 *
 */

#ifndef STATICSYSTEM_HPP_
#define STATICSYSTEM_HPP_

#include "../Coordinator.hpp"
#include "../System.hpp"
#include "../components/Position.hpp"
#include "../components/Velocity.hpp"
#include "../components/StaticType.hpp"
#include "../components/Hitbox.hpp"

/**
 * @class StaticSystem
 * @brief Class of the Static system
 *
 */
class StaticSystem : public System {
public:
    /**
     * @brief Update the Static system using the entities stocker in the coordinator
     * @param coordinator : The coordinator of the ECS
     */
    void Update(Coordinator &coordinator);

protected:
private:
};

#include "../../src/systems/StaticSystem.cpp"

#endif /* !STATICSYSTEM_HPP_ */
