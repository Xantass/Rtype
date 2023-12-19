/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** ParallaxSystem
*/

#include "../System.hpp"
#include "../Coordinator.hpp"
#include "../components/Position.hpp"
#include "../components/Sprite.hpp"

#ifndef PARALLAXSYSTEM_HPP_
#define PARALLAXSYSTEM_HPP_

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

#endif /* !PARALLAXSYSTEM_HPP_ */
