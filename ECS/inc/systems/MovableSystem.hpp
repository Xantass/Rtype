/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** MovableSystem
*/

#ifndef MOVABLESYSTEM_HPP_
#define MOVABLESYSTEM_HPP_

#include "../Coordinator.hpp"
#include "../System.hpp"
#include "../components/Movable.hpp"
#include "../components/Velocity.hpp"
#include "../Event.hpp"

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

#endif /* !MOVABLESYSTEM_HPP_ */
