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

class MovableSystem : public System {
    public:

        void Update(Coordinator &coordinator);

    protected:
    private:
};

#endif /* !MOVABLESYSTEM_HPP_ */
