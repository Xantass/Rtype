/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** ControlSystem.hpp
*/

#ifndef CONTROLSYSTEM_HPP_
#define CONTROLSYSTEM_HPP_

#include "../Coordinator.hpp"
#include "../System.hpp"
#include "../components/Controllable.hpp"
#include "../components/Velocity.hpp"
#include "../components/Position.hpp"

/**
 * @class ControlSystem
 * @brief Class of the Control system
 *
 */
class ControlSystem : public System {
    public:
        /**
         * @brief Update the control system using the entities stocker in the coordinator
         * @param coordinator : The coordinator of the ECS
         */
        void Update(Coordinator &coordinator);

    protected:
    private:
};

#include "../../src/systems/ControlSystem.cpp"

#endif /* !CONTROLSYSTEM_HPP_ */
