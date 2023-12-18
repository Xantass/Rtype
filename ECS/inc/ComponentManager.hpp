/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** ComponentManager
*/

/**
 * @file ComponentManager.hpp
 * @brief File containing the ComponentManager class
 * 
 */

#ifndef COMPONENTMANAGER_HPP_
#define COMPONENTMANAGER_HPP_

#include <iostream>
#include <unordered_map>
#include <memory>
#include <typeindex>

#include "ComponentArray.hpp"
#include "Entity.hpp"
#include "components/ComponentType.hpp"

/**
 * @class ComponentManager
 * @brief Class of the component manager
 * @details The ComponentManager class is a class that manages the components of the entities.
 * 
 */
class ComponentManager {
	public:
		/**
		 * @brief Register a new component type
		 * 
		 * @tparam T Type of the component
		 */
		template<typename T>
		void RegisterComponent();
		/**
		 * @brief Get the Component Type object
		 * 
		 * @tparam T Type of the component
		 * @return ComponentType Type of the component
		 */
		template<typename T>
		ComponentType GetComponentType();
		/**
		 * @brief Add a component to an entity
		 * 
		 * @tparam T Type of the component
		 * @param entity Entity to add the component to
		 * @param component Component to add to the entity
		 */
		template<typename T>
		void AddComponent(Entity entity, T component);
		/**
		 * @brief Remove a component from an entity
		 * 
		 * @tparam T Type of the component
		 * @param entity Entity to remove the component from
		 */
		template<typename T>
		void RemoveComponent(Entity entity);
		/**
		 * @brief Get a reference of a component from an entity
		 * 
		 * @tparam T Type of the component
		 * @param entity Entity to get the component's reference from
		 * @return T& Component of the entity
		 */
		template<typename T>
		T& GetComponent(Entity entity);
		/**
		 * @brief Notify the component manager that an entity has been destroyed
		 * 
		 * @param entity Entity that has been destroyed
		 */
		void EntityDestroyed(Entity entity);
	private:
		/**
		 * @brief Map to store the type of the components registered
		 * 
		 */
		std::unordered_map<std::type_index, ComponentType> _componentTypes;
		/**
		 * @brief Map to store a reference the component arrays
		 * 
		 */
		std::unordered_map<std::type_index, std::shared_ptr<IComponentArray>> _componentArrays{};
		/**
		 * @brief Component type to be assigned to the next registered component
		 * @details The component type is used to create the signature of the entity, which is used to know which components an entity has.
		 * 
		 */
		ComponentType _nextComponentType{};
		/**
		 * @brief Get the Component Array object
		 * @details Utils function to get the casted pointer to the ComponentArray of type T.
		 * 
		 * @tparam T Type of the component
		 * @return std::shared_ptr<ComponentArray<T>> Pointer to the component array
		 */
		template<typename T>
		std::shared_ptr<ComponentArray<T>> GetComponentArray()
		{
			std::type_index typeName = std::type_index(typeid(T));
		// if (_componentTypes.find(typeName) == _componentTypes.end()) {
			// ERROR : "Component not registered before use."
		// }
		return std::static_pointer_cast<ComponentArray<T>>(_componentArrays[typeName]);
		}
};

#endif /* !COMPONENTMANAGER_HPP_ */
