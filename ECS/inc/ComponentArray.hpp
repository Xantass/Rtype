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
#include <cstddef>

#include "Entity.hpp"
#include "components/Position.hpp"
#include "components/Velocity.hpp"
#include "components/Hitbox.hpp"
#include "components/Sprite.hpp"
#include "components/Movable.hpp"

/**
 * @interface IComponentArray
 * @brief Interface for the ComponentArray class
 * @details An interface is needed so that the ComponentManager can tell a generic ComponentArray that an entity has been destroyed and that it needs to update its array mappings.
 * 
 */
class IComponentArray {
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
class ComponentArray : public IComponentArray {
public:
	/**
	 * @brief Link a new component to an entity
	 * 
	 * @param entity Entity to link the component to
	 * @param component Component to link to the entity
	 */
	void InsertData(Entity entity, T component);

	/**
	 * @brief Remove an entity and its components
	 * 
	 * @param entity Entity to remove
	 */
	void RemoveData(Entity entity);

	/**
	 * @brief Get the component of an entity
	 * 
	 * @param entity Entity to get the component from
	 * @return T& Reference to the component
	 */
	T& GetData(Entity entity);

	/**
	 * @brief Called when an entity is destroyed so that the component array can update its references
	 * 
	 * @param entity Entity destroyed
	 */
	void EntityDestroyed(Entity entity) override;

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
