/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** GravitySystem
*/

#ifndef GRAVITYSYSTEM_HPP_
#define GRAVITYSYSTEM_HPP_

#include "System.hpp"
#include "components/Velocity.hpp"
#include "components/Falling.hpp"

/**
 * @class GravitySystem
 * @brief Class of the gravity system
 *
 */
class GravitySystem : public System {
    public:
        /**
         * @brief Update the gravity system using the entities stocker in the coordinator
         * @param coordinator : The coordinator of the ECS
         */
        void Update(Coordinator &coordinator);
    protected:
    private:
};

#include "../../src/systems/GravitySystem.cpp"

#endif /* !GRAVITYSYSTEM_HPP_ */
