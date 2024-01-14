/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** CollisionSystem.hpp
*/

#ifndef COLLISIONSYSTEM_HPP_
#define COLLISIONSYSTEM_HPP_

#include "System.hpp"
#include "components/Velocity.hpp"
#include "components/Position.hpp"
#include "components/FlappyHitBox.hpp"

/**
 * @class CollisionSystem
 * @brief Class of the Collision system
 *
 */
class CollisionSystem2 : public System {
    public:
        /**
         * @brief Update the collision system using the entities stocker in the coordinator
         * @param coordinator : The coordinator of the ECS
         */
        void Update(Coordinator &coordinator);

    protected:
    private:
};

#include "../../src/systems/FlappyCollisionSystem.cpp"

#endif /* !COLLISIONSYSTEM_HPP_ */
