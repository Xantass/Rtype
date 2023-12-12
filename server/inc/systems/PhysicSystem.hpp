/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** PhysicSystem
*/

#ifndef PHYSICSYSTEM_HPP_
#define PHYSICSYSTEM_HPP_

#include <iostream>

#include "../System.hpp"
#include "../Coordinator.hpp"

// extern Coordinator gCoordinator;

class PhysicSystem : public System {
public:

    void Update(Coordinator &coordinator) {
        std::cout << "PhysicSystem update :" << std::endl;
        for (auto entity : mEntities) {
            auto& pos = coordinator.GetComponent<Position>(entity);
            auto& vel = coordinator.GetComponent<Velocity>(entity);

            pos.x += vel.x;
            pos.y += vel.y;

            std::cout << "Entity position : " << pos.x << " " << pos.y << std::endl;
        }
    };

protected:
private:
};

#endif /* !PHYSICSYSTEM_HPP_ */
