/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** HealthSystem.hpp
*/

/**
 * @file HealthSystem.hpp
 * @brief File containing the HealthSystem class
 *
 */

#ifndef HEALTHSYSTEM_HPP_
#define HEALTHSYSTEM_HPP_

#include "System.hpp"
#include "components/HealthPoint.hpp"

/**
 * @class HealthSystem
 * @brief Class of the Health system
 *
 */
class HealthSystem : public System {
public:
    /**
     * @brief Update the health system using the entities stocker in the coordinator
     * @param coordinator : The coordinator of the ECS
     */
    void Update(Coordinator &coordinator);

protected:
private:
};

#include "../../src/systems/HealthSystem.cpp"

#endif /* !HEALTHSYSTEM_HPP_ */
