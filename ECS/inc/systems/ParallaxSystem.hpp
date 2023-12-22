/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** ParallaxSystem
*/

/**
 * @file ParallaxSystem.hpp
 * @brief File containing the ParallaxSystem class
 *
 */

#ifndef PARALLAXSYSTEM_HPP_
#define PARALLAXSYSTEM_HPP_

#include "System.hpp"
#include "components/Position.hpp"
#include "components/Velocity.hpp"
#include "components/Hitbox.hpp"
#include "components/Sprite.hpp"
#include "components/Movable.hpp"

/**
 * @class ParallaxSystem
 * @brief Class of the parallax system
 *
 */
class ParallaxSystem : public System {
public:

    /**
     * @brief Update the parallax system using the entities stocker in the coordinator
     * @param coordinator : The coordinator of the ECS
     *
     */
    void Update(Coordinator &coordinator);

protected:
private:
};

#include "../../src/systems/ParallaxSystem.cpp"

#endif /* !PARALLAXSYSTEM_HPP_ */
