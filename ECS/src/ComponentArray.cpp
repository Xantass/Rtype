/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** ComponentArray
*/

#include "ComponentArray.hpp"

template <typename T>
void ComponentArray<T>::InsertData(Entity entity, T component)
{
    if (this->_entityToIndex.find(entity) == this->_entityToIndex.end()) {
        // ERROR : Component added to same entity more than once.
    }
	// Put new entry at end and update the maps
	std::size_t newIndex = this->_arraySize;

	this->_entityToIndex[entity] = newIndex;
	this->_indexToEntity[newIndex] = entity;
	this->_componentArray[newIndex] = component;
	this->_arraySize++;
}

template <typename T>
void ComponentArray<T>::RemoveData(Entity entity)
{
	if (this->_entityToIndex.find(entity) == this->_entityToIndex.end()) {
		// ERROR : "Retrieving non-existent component."
	}
	// Copy element at end into deleted element's place to maintain density
	std::size_t indexOfRemovedEntity = this->_entityToIndex[entity];
	std::size_t indexOfLastElement = this->_arraySize - 1;
	Entity entityOfLastElement = this->_indexToEntity[indexOfLastElement];

	// Update map to point to moved spot
	this->_componentArray[indexOfRemovedEntity] = this->_componentArray[indexOfLastElement];
	this->_entityToIndex[entityOfLastElement] = indexOfRemovedEntity;
	this->_indexToEntity[indexOfRemovedEntity] = entityOfLastElement;
	this->_entityToIndex.erase(entity);
	this->_indexToEntity.erase(indexOfLastElement);
	this->_arraySize--;
}

template <typename T>
T& ComponentArray<T>::GetData(Entity entity)
{
	if (this->_entityToIndex.find(entity) == this->_entityToIndex.end()) {
		// ERROR : "Retrieving non-existent component."
	}
	return this->_componentArray[this->_entityToIndex[entity]];
}

template <typename T>
void ComponentArray<T>::EntityDestroyed(Entity entity)
{
	if (this->_entityToIndex.find(entity) == this->_entityToIndex.end())
		RemoveData(entity);
}
