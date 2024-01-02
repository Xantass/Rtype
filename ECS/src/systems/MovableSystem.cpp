/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** MovableSystem
*/

#include "systems/MovableSystem.hpp"
#include "Graphic.hpp"

void MovableSystem::Update(Coordinator &coordinator)
{
    // std::cout << "MovableSystem update :" << std::endl;
    for (auto &entity : this->_entities) {
        auto& mov = coordinator.GetComponent<Movable>(entity);
        auto& vel = coordinator.GetComponent<Velocity>(entity);

        if (IsKeyPressed(KEY_SPACE)) {
            coordinator.AddEvent(Event{Event::actions::SHOOT, 0, std::any(Velocity{1, 0})});
        } else if (IsKeyPressed(KEY_W)) {
            coordinator.AddEvent(Event{Event::actions::MOVE, entity, std::any(Velocity{0, -1})});
            vel = {vel._x, -1};
        } else if (Graphic::isKeyDown(KEY_D)) {
            coordinator.AddEvent(Event{Event::actions::MOVE, entity, std::any(Velocity{1, 0})});
            vel = {1, vel._y};
        } else if (Graphic::isKeyDown(KEY_S)) {
            coordinator.AddEvent(Event{Event::actions::MOVE, entity, std::any(Velocity{0, 1})});
            vel = {vel._x, 1};
        } else if (Graphic::isKeyDown(KEY_A)) {
            coordinator.AddEvent(Event{Event::actions::MOVE, entity, std::any(Velocity{-1, 0})});
            vel = {-1, vel._y};
        } else if (Graphic::isKeyUp(KEY_W) || Graphic::isKeyUp(KEY_D) || Graphic::isKeyUp(KEY_S) || Graphic::isKeyUp(KEY_A)) {
            coordinator.AddEvent(Event{Event::actions::MOVE, entity, std::any(Velocity{0, 0})});
            vel = {0, 0};
        }
    }
}