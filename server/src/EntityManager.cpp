/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** EntityManager
*/

#include "EntityManager.hpp"

EntityManager::EntityManager()
{
    for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
		{
			_availableEntities.push(entity);
		}
}

EntityManager::~EntityManager()
{
}

Entity EntityManager::CreateEntity()
{
    if (_livingEntityCount < MAX_ENTITIES) {
        //ERROR : Too many entities in existence.
    }

    Entity id = _availableEntities.front();
    _availableEntities.pop();
    ++_livingEntityCount;

    return id;
}

void EntityManager::DestroyEntity(Entity entity)
{
    if (entity >= MAX_ENTITIES) {
        //ERROR : Entity out of range.
    }

    _signatures[entity].reset();
    _availableEntities.push(entity);
    --_livingEntityCount;
}

void EntityManager::SetSignature(Entity entity, Signature signature)
{
    if (entity >= MAX_ENTITIES) {
        //ERROR : Entity out of range.
    }

    _signatures[entity] = signature;
}

Signature EntityManager::GetSignature(Entity entity)
{
    if (entity >= MAX_ENTITIES) {
        //ERROR : Entity out of range.
    }

    return _signatures[entity];
}