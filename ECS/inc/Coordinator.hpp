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
class Coordinator
{
public:

	/**
	 * @brief Initialize the coordinator
	 * @details This method initializes the coordinator by creating pointers to each manager.
	 * 
	 */
	void Init() {
		this->_componentManager = std::make_unique<ComponentManager>();
		this->_entityManager = std::make_unique<EntityManager>();
		this->_systemManager = std::make_unique<SystemManager>();
	}

	/* ----------------------------- Entity methods ----------------------------- */

	/**
	 * @brief Create an entity
	 * @details This method creates an entity by calling the CreateEntity method of the EntityManager.
	 * 
	 * @return Entity Entity created
	 */
	Entity CreateEntity() {
		return this->_entityManager->CreateEntity();
	}

	/**
	 * @brief Create an entity with a specific id
	 * @details This method creates an entity by calling the CreateEntity method of the EntityManager.
	 * 
	 * @param id Id of the entity
	 * @return Entity Entity created
	 */
	Entity CreateEntity(int id) {
		return this->_entityManager->CreateEntity(id);
	}

	/**
	 * @brief Destroy an entity
	 * @details This method destroys an entity by calling the DestroyEntity method of the EntityManager and the EntityDestroyed method of the ComponentManager and the SystemManager.
	 * 
	 * @param entity Entity to be destroyed
	 */
	void DestroyEntity(Entity entity) {
		this->_entityManager->DestroyEntity(entity);

		this->_componentManager->EntityDestroyed(entity);

		this->_systemManager->EntityDestroyed(entity);
	}

	/* --------------------------- Components methods --------------------------- */

	/**
	 * @brief Register a component type
	 * 
	 * @tparam T Type of the component
	 */
	template<typename T>
	void RegisterComponent() {
		this->_componentManager->RegisterComponent<T>();
	}

	/**
	 * @brief Add a component to an entity
	 * @details This method also update the signature of the entity with the new Component added.
	 * 
	 * @tparam T Type of the component to add
	 * @param entity Entity to add the component to
	 * @param component Values of the component
	 */
	template<typename T>
	void AddComponent(Entity entity, T component) {
		this->_componentManager->AddComponent<T>(entity, component);

		auto signature = this->_entityManager->GetSignature(entity);
		signature.set(this->_componentManager->GetComponentType<T>(), true);
		this->_entityManager->SetSignature(entity, signature);

		this->_systemManager->EntitySignatureChanged(entity, signature);
	}

	/**
	 * @brief Remove a component from an entity
	 * @details This method also update the signature of the entity with the Component removed.
	 * 
	 * @tparam T Type of the component to remove
	 * @param entity Entity to remove the component from
	 */
	template<typename T>
	void RemoveComponent(Entity entity) {
		this->_componentManager->RemoveComponent<T>(entity);

		auto signature = this->_entityManager->GetSignature(entity);
		signature.set(this->_componentManager->GetComponentType<T>(), false);
		this->_entityManager->SetSignature(entity, signature);

		this->_systemManager->EntitySignatureChanged(entity, signature);
	}

	/**
	 * @brief Get a reference of a component from an entity
	 * @details This can be use to get the values of a component from an entity.
	 * 
	 * @tparam T Type of the component
	 * @param entity Entity to get the component's reference from
	 * @return T& Component of the entity
	 */
	template<typename T>
	T& GetComponent(Entity entity) {
		return this->_componentManager->GetComponent<T>(entity);
	}

	/**
	 * @brief Get the Component Type object
	 * 
	 * @tparam T Type of the component
	 * @return ComponentType Type of the component
	 */
	template<typename T>
	ComponentType GetComponentType() {
		return this->_componentManager->GetComponentType<T>();
	}

	/* ----------------------------- System methods ----------------------------- */

	/**
	 * @brief Register a system
	 * 
	 * @tparam T Type of the system
	 * @return std::shared_ptr<T> Pointer to the system
	 */
	template<typename T>
	std::shared_ptr<T> RegisterSystem() {
		return this->_systemManager->RegisterSystem<T>();
	}

	/**
	 * @brief Set the System Signature object
	 * @details This method set the signature of the system with the signature passed in parameter.
	 * 
	 * @tparam T Type of the system
	 * @param signature Signature to set
	 */
	template<typename T>
	void SetSystemSignature(Signature signature) {
		this->_systemManager->SetSignature<T>(signature);
	}

	/**
	 * @brief Add an event to the queue
	 * 
	 * @param event Event to add
	 */
	void AddEvent(Event event) {
		this->_eventQueue.push(event);
	}

	/**
	 * @brief Get the first event of the queue
	 * 
	 * @return Event First event of the queue
	 */
	Event GetEvent() {
		Event event = this->_eventQueue.front();
		this->_eventQueue.pop();
		return event;
	}

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

	/**
	 * @brief Queue of events
	 * 
	 */
	std::queue<Event> _eventQueue;
};

#endif /* !COORDINATOR_HPP_ */
