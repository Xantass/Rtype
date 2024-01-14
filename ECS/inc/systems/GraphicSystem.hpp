/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** GraphicalSystem
*/

#ifndef GRAPHICALSYSTEM_HPP_
#define GRAPHICALSYSTEM_HPP_

#include "System.hpp"
#include "components/Position.hpp"
#include "components/Sprite.hpp"

/**
 * @class GraphicSystem
 * @brief Class of the graphic system
 *
 */
class GraphicSystem : public System {
    public:
        /**
         * @brief Update the graphic system using the entities stocker in the coordinator
         * @param coordinator : The coordinator of the ECS
         */
        void Update(Coordinator &coordinator);
    protected:
    private:
};

#include "../../src/systems/GraphicSystem.cpp"

#endif /* !GRAPHICALSYSTEM_HPP_ */
