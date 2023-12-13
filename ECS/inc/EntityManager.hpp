/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** EntityManager
*/

#ifndef ENTITYMANAGER_HPP_
#define ENTITYMANAGER_HPP_

#include <queue>
#include <array>

#include "Signature.hpp"
#include "Entity.hpp"

class EntityManager {
public:
    EntityManager();
    ~EntityManager();

	Entity CreateEntity();

	void DestroyEntity(Entity entity);

	void SetSignature(Entity entity, Signature signature);

	Signature GetSignature(Entity entity);

protected:
private:
	std::queue<Entity> _availableEntities{};
	uint32_t _livingEntityCount{};
	std::array<Signature, MAX_ENTITIES> _signatures{};
};

#endif /* !ENTITYMANAGER_HPP_ */
