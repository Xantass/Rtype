/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** GraphicalSystem
*/

#ifndef GRAPHICALSYSTEM_HPP_
#define GRAPHICALSYSTEM_HPP_

#include "../Coordinator.hpp"
#include "../System.hpp"
#include "../components/Position.hpp"
#include "../components/Sprite.hpp"
/**
 * @class GraphicalSystem
 * @brief Class of the graphical system
 *
 */
class GraphicalSystem : public System {
    public:
        /**
         * @brief Update the graphical system using the entities stocker in the coordinator
         * @param coordinator : The coordinator of the ECS
         */
        void Update(Coordinator &coordinator);
    protected:
    private:
};

#endif /* !GRAPHICALSYSTEM_HPP_ */
