/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** Coordinator
*/

/**
 * @file Coordinator.hpp
 * @brief File containing the Coordinator class
 * 
 */

#ifndef COORDINATOR_HPP_
#define COORDINATOR_HPP_

#include <memory>
#include <queue>
#include "ComponentManager.hpp"
#include "EntityManager.hpp"
#include "SystemManager.hpp"
#include "Event.hpp"

/**
 * @class Coordinator
 * @brief Class of the coordinator
 * @details The Coordinator class is a class that manages the ECS.
 * 
 */
class Coordinator {
	public:
		/**
		 * @brief Initialize the coordinator
		 * @details This method initializes the coordinator by creating pointers to each manager.
		 * 
		 */
		void Init();

		/* ----------------------------- Entity methods ----------------------------- */
		/**
		 * @brief Create an entity
		 * @details This method creates an entity by calling the CreateEntity method of the EntityManager.
		 * 
		 * @return Entity Entity created
		 */
		Entity CreateEntity();

		/**
		 * @brief Destroy an entity
		 * @details This method destroys an entity by calling the DestroyEntity method of the EntityManager and the EntityDestroyed method of the ComponentManager and the SystemManager.
		 * 
		 * @param entity Entity to be destroyed
		 */
		void DestroyEntity(Entity entity);

		/* --------------------------- Components methods --------------------------- */

		/**
		 * @brief Register a component type
		 * 
		 * @tparam T Type of the component
		 */
		template<typename T>
		void RegisterComponent();
		/**
		 * @brief Add a component to an entity
		 * @details This method also update the signature of the entity with the new Component added.
		 * 
		 * @tparam T Type of the component to add
		 * @param entity Entity to add the component to
		 * @param component Values of the component
		 */
		template<typename T>
		void AddComponent(Entity entity, T component);
		/**
		 * @brief Remove a component from an entity
		 * @details This method also update the signature of the entity with the Component removed.
		 * 
		 * @tparam T Type of the component to remove
		 * @param entity Entity to remove the component from
		 */
		template<typename T>
		void RemoveComponent(Entity entity);
		/**
		 * @brief Get a reference of a component from an entity
		 * @details This can be use to get the values of a component from an entity.
		 * 
		 * @tparam T Type of the component
		 * @param entity Entity to get the component's reference from
		 * @return T& Component of the entity
		 */
		template<typename T>
		T& GetComponent(Entity entity);
		/**
		 * @brief Get the Component Type object
		 * 
		 * @tparam T Type of the component
		 * @return ComponentType Type of the component
		 */
		template<typename T>
		ComponentType GetComponentType();

		/* ----------------------------- System methods ----------------------------- */
	
		/**
		 * @brief Register a system
		 * 
		 * @tparam T Type of the system
		 * @return std::shared_ptr<T> Pointer to the system
		 */
		template<typename T>
		std::shared_ptr<T> RegisterSystem();
		/**
		 * @brief Set the System Signature object
		 * @details This method set the signature of the system with the signature passed in parameter.
		 * 
		 * @tparam T Type of the system
		 * @param signature Signature to set
		 */
		template<typename T>
		void SetSystemSignature(Signature signature);
	private:
		/**
		 * @brief Pointer to the component manager
		 * 
		 */
		std::unique_ptr<ComponentManager> _componentManager;
		/**
		 * @brief Pointer to the entity manager
		 * 
		 */
		std::unique_ptr<EntityManager> _entityManager;
		/**
		 * @brief Pointer to the system manager
		 * 
		 */
		std::unique_ptr<SystemManager> _systemManager;
};

#endif /* !COORDINATOR_HPP_ */
