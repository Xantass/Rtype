/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** EntityManager
*/

#include "EntityManager.hpp"

inline EntityManager::EntityManager() {
    for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
        this->_availableEntities.push_back(entity);
}

inline EntityManager::~EntityManager() {
}

inline Entity EntityManager::CreateEntity() {
    if (this->_livingEntityCount < MAX_ENTITIES) {
        //ERROR : Too many entities in existence.
    }

    Entity id = this->_availableEntities.front();
    this->_availableEntities.erase(this->_availableEntities.begin());
    this->_livingEntityCount++;

    return id;
}

inline Entity EntityManager::CreateEntity(int id) {
    if (id >= static_cast<int>(MAX_ENTITIES)) {
        //ERROR : Entity out of range.
    }

    Entity entity = id;
    this->_livingEntityCount++;
    (void)entity;

    return id;
}

inline void EntityManager::DestroyEntity(Entity entity) {
    if (entity >= MAX_ENTITIES) {
        //ERROR : Entity out of range.
    }

    this->_signatures[entity].reset();
    this->_availableEntities.insert(this->_availableEntities.begin(), entity);
    this->_livingEntityCount--;
}

inline void EntityManager::SetSignature(Entity entity, Signature signature) {
    if (entity >= MAX_ENTITIES) {
        //ERROR : Entity out of range.
    }

    _signatures[entity] = signature;
}

inline Signature EntityManager::GetSignature(Entity entity) {
    if (entity >= MAX_ENTITIES) {
        //ERROR : Entity out of range.
    }

    return this->_signatures[entity];
}