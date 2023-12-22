/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** MovableSystem
*/

#ifndef MOVABLESYSTEM_HPP_
#define MOVABLESYSTEM_HPP_

#include "raylib.h"

// class Coordinator {};

#include "System.hpp"
#include "components/Position.hpp"
#include "components/Velocity.hpp"
#include "components/Hitbox.hpp"
#include "components/Sprite.hpp"
#include "components/Movable.hpp"


class MovableSystem : public System {
    public:

        void Update(Coordinator &coordinator);

    protected:
    private:
};

#include "../../src/systems/MovableSystem.cpp"

#endif /* !MOVABLESYSTEM_HPP_ */
