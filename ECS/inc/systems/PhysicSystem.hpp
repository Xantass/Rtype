/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** PhysicSystem
*/

/**
 * @file PhysicSystem.hpp
 * @brief File containing the PhysicSystem class
 * 
 */

#ifndef PHYSICSYSTEM_HPP_
#define PHYSICSYSTEM_HPP_

// class Coordinator {};

#include "System.hpp"
#include "components/Position.hpp"
#include "components/Velocity.hpp"
#include "components/Hitbox.hpp"

#include <iostream>

/**
 * @class PhysicSystem
 * @brief Class of the physic system
 * 
 */
class PhysicSystem : public System {
    public:
        /**
         * @brief Update the physic system using the entities stocker in the coordinator
         * @param coordinator : The coordinator of the ECS
         * 
         */
        void Update(Coordinator &coordinator);
    protected:
    private:
};

#include "../../src/systems/PhysicSystem.cpp"

#endif /* !PHYSICSYSTEM_HPP_ */
