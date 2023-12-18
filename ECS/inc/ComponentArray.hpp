/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** ComponentArray
*/

/**
 * @file ComponentArray.hpp
 * @brief File containing the ComponentArray class
 * 
 */

#ifndef COMPONENTARRAY_HPP_
#define COMPONENTARRAY_HPP_

#include <array>
#include <unordered_map>

#include "Entity.hpp"

/**
 * @interface IComponentArray
 * @brief Interface for the ComponentArray class
 * @details An interface is needed so that the ComponentManager can tell a generic ComponentArray that an entity has been destroyed and that it needs to update its array mappings.
 * 
 */
class IComponentArray
{
public:
	/**
	 * @brief Destroy the IComponentArray object
	 * 
	 */
	virtual ~IComponentArray() = default;

	/**
	 * @brief Called when an entity is destroyed so that the component array can update its references
	 * 
	 * @param entity Entity to be destroyed
	 */
	virtual void EntityDestroyed(Entity entity) = 0;
};

/**
 * @class ComponentArray
 * @brief Class of the component array
 * @details The ComponentArray class is a template class that stores the components of a specific type T.
 * 
 * @tparam T Type of the component
 */
template<typename T>
class ComponentArray : public IComponentArray
{
public:

	/**
	 * @brief Link a new component to an entity
	 * 
	 * @param entity Entity to link the component to
	 * @param component Component to link to the entity
	 */
	void InsertData(Entity entity, T component) {
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

	/**
	 * @brief Remove an entity and its components
	 * 
	 * @param entity Entity to remove
	 */
	void RemoveData(Entity entity) {
		if (this->_entityToIndex.find(entity) == this->_entityToIndex.end()) {
			// ERROR : "Retrieving non-existent component."
		}

		// Copy element at end into deleted element's place to maintain density
		std::size_t indexOfRemovedEntity = this->_entityToIndex[entity];
		std::size_t indexOfLastElement = this->_arraySize - 1;
		this->_componentArray[indexOfRemovedEntity] = this->_componentArray[indexOfLastElement];

		// Update map to point to moved spot
		Entity entityOfLastElement = this->_indexToEntity[indexOfLastElement];
		this->_entityToIndex[entityOfLastElement] = indexOfRemovedEntity;
		this->_indexToEntity[indexOfRemovedEntity] = entityOfLastElement;

		this->_entityToIndex.erase(entity);
		this->_indexToEntity.erase(indexOfLastElement);

		this->_arraySize--;
	}

	/**
	 * @brief Get the component of an entity
	 * 
	 * @param entity Entity to get the component from
	 * @return T& Reference to the component
	 */
	T& GetData(Entity entity) {
		if (this->_entityToIndex.find(entity) == this->_entityToIndex.end()) {
			// ERROR : "Retrieving non-existent component."
		}

		return this->_componentArray[this->_entityToIndex[entity]];
	}

	/**
	 * @brief Called when an entity is destroyed so that the component array can update its references
	 * 
	 * @param entity Entity destroyed
	 */
	void EntityDestroyed(Entity entity) override {
		if (this->_entityToIndex.find(entity) == this->_entityToIndex.end())
			RemoveData(entity);
	}

private:
	/**
	 * @brief Array of components for each type T
	 * 
	 */
	std::array<T, MAX_ENTITIES> _componentArray;

	/**
	 * @brief Map from an entity ID to an array index
	 * 
	 */
	std::unordered_map<Entity, std::size_t> _entityToIndex;

	/**
	 * @brief Map from an array index to an entity ID
	 * 
	 */
	std::unordered_map<std::size_t, Entity> _indexToEntity;

	/**
	 * @brief Size of the array
	 * 
	 */
	std::size_t _arraySize;
};

#endif /* !COMPONENTARRAY_HPP_ */
