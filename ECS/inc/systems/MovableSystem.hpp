/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** MovableSystem
*/

/**
 * @file MovableSystem.hpp
 * @brief File containing the MovableSystem class
 *
 */

#ifndef MOVABLESYSTEM_HPP_
#define MOVABLESYSTEM_HPP_

#include "raylib.h"

#include "System.hpp"
#include "components/Position.hpp"
#include "components/Velocity.hpp"
#include "components/Hitbox.hpp"
#include "components/Sprite.hpp"
#include "components/Movable.hpp"


/**
 * @class MovableSystem
 * @brief Class of the Movable system
 *
 */
class MovableSystem : public System {
public:
    /**
     * @brief Update the movable system using the entities stocker in the coordinator
     * @param coordinator : The coordinator of the ECS
     */
    void Update(Coordinator &coordinator);

protected:
private:
};

#include "../../src/systems/MovableSystem.cpp"

#endif /* !MOVABLESYSTEM_HPP_ */
