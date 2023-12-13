/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** PhysicSystem
*/

#ifndef PHYSICSYSTEM_HPP_
#define PHYSICSYSTEM_HPP_


#include "../System.hpp"
#include "../Coordinator.hpp"
#include "../components/Position.hpp"
#include "../components/Velocity.hpp"

class PhysicSystem : public System {
public:

    void Update(Coordinator &coordinator);

protected:
private:
};

#endif /* !PHYSICSYSTEM_HPP_ */
