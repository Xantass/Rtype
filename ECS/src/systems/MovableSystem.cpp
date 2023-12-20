/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** MovableSystem
*/

#include "systems/MovableSystem.hpp"
#if defined(_WIN32)           
	#define NOGDI             // All GDI defines and routines
	#define NOUSER            // All USER defines and routines
#endif

#include "raylib.h" // or any library that uses Windows.h

#if defined(_WIN32)           // raylib uses these names as function parameters
	#undef near
	#undef far
#endif

void MovableSystem::Update(Coordinator &coordinator)
{
    // std::cout << "MovableSystem update :" << std::endl;
    for (auto &entity : this->_entities) {
        auto& mov = coordinator.GetComponent<Movable>(entity);
        auto& vel = coordinator.GetComponent<Velocity>(entity);

        if (IsKeyPressed(KEY_W)) {
            coordinator.AddEvent(Event{Event::actions::MOVE, entity, std::any(Velocity{0, -1})});
            vel = {0, -1};
        } else if (IsKeyPressed(KEY_D)) {
            coordinator.AddEvent(Event{Event::actions::MOVE, entity, std::any(Velocity{1, 0})});
            vel = {1, 0};
        } else if (IsKeyPressed(KEY_S)) {
            coordinator.AddEvent(Event{Event::actions::MOVE, entity, std::any(Velocity{0, 1})});
            vel = {0, 1};
        } else if (IsKeyPressed(KEY_A)) {
            coordinator.AddEvent(Event{Event::actions::MOVE, entity, std::any(Velocity{-1, 0})});
            vel = {-1, 0};
        } else if (IsKeyReleased(KEY_W) || IsKeyReleased(KEY_D) || IsKeyReleased(KEY_S) || IsKeyReleased(KEY_A)) {
            vel = {0, 0};
        }
    }
}