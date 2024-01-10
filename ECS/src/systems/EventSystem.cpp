/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** EventSystem
*/

#include "EventSystem.hpp"

#include "components/Sprite.hpp"
#include "components/Controllable.hpp"
#include "Graphic.hpp"

void EventSystem::RunEvents(Coordinator &coordinator)
{
	std::queue<Event> eventQueue = coordinator.GetEventQueue();

	// std::cout << "EventSystem, last event: " << event._type << std::endl;

	while (!eventQueue.empty()) {
		Event event = eventQueue.front();
		eventQueue.pop();
		switch (event._type) {
			case Event::actions::CREATE: {
				Entity entity = coordinator.CreateEntity(std::any_cast<int>(event._data[0]));
				coordinator.AddComponent<Position>(entity, {std::any_cast<float>(event._data[1]), std::any_cast<float>(event._data[2])});
				coordinator.AddComponent<Velocity>(entity, {std::any_cast<float>(event._data[3]), std::any_cast<float>(event._data[4])});
				coordinator.AddComponent<Hitbox>(entity, {std::any_cast<float>(event._data[5]), std::any_cast<float>(event._data[6]), std::any_cast<float>(event._data[7]), std::any_cast<float>(event._data[8]), std::any_cast<HitboxType>(event._data[9])});
				if (std::any_cast<HitboxType>(event._data[9]) == (PLAYER))
					coordinator.AddComponent<Sprite>(entity, {Graphic::loadTexture("assets/spaceship.png")});
				if (std::any_cast<int>(event._data[10]) == static_cast<int>(entity))
					coordinator.AddComponent<Movable>(entity, {NONE});
				if (std::any_cast<HitboxType>(event._data[9]) == (BULLET))
					coordinator.AddComponent<Sprite>(entity, {Graphic::loadTexture("assets/bullets.png")});
				if (std::any_cast<HitboxType>(event._data[9]) == (ENNEMY))
					coordinator.AddComponent<Sprite>(entity, {Graphic::loadTexture("assets/carli.png")});
				break;
			} case Event::actions::MOVE: {
				coordinator.GetComponent<Position>(event._entity)._x += coordinator.GetComponent<Velocity>(event._entity)._x;
				coordinator.GetComponent<Position>(event._entity)._y += coordinator.GetComponent<Velocity>(event._entity)._y;
				break;
			} case Event::actions::DESTROY: {
				coordinator.DestroyEntity(event._entity);
				break;
			} default:
				break;
		}
	}
}