/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** Coordinator
*/

#include "Coordinator.hpp"

inline void Coordinator::Init()
{
	this->_componentManager = std::make_unique<ComponentManager>();
	this->_entityManager = std::make_unique<EntityManager>();
	this->_systemManager = std::make_unique<SystemManager>();
}

inline Entity Coordinator::CreateEntity()
{
	return this->_entityManager->CreateEntity();
}

inline void Coordinator::DestroyEntity(Entity entity)
{
	this->_entityManager->DestroyEntity(entity);
	this->_componentManager->EntityDestroyed(entity);
	this->_systemManager->EntityDestroyed(entity);
}

template<typename T>
inline void Coordinator::RegisterComponent()
{
	this->_componentManager->RegisterComponent<T>();
}

template<typename T>
inline void Coordinator::AddComponent(Entity entity, T component)
{
	auto signature = this->_entityManager->GetSignature(entity);

	this->_componentManager->AddComponent<T>(entity, component);
	signature.set(this->_componentManager->GetComponentType<T>(), true);
	this->_entityManager->SetSignature(entity, signature);
	this->_systemManager->EntitySignatureChanged(entity, signature);
}

template<typename T>
inline void Coordinator::RemoveComponent(Entity entity)
{
	auto signature = this->_entityManager->GetSignature(entity);

	this->_componentManager->RemoveComponent<T>(entity);
	signature.set(this->_componentManager->GetComponentType<T>(), false);
	this->_entityManager->SetSignature(entity, signature);
	this->_systemManager->EntitySignatureChanged(entity, signature);
}

template<typename T>
inline T& Coordinator::GetComponent(Entity entity)
{
	return this->_componentManager->GetComponent<T>(entity);
}

template<typename T>
inline ComponentType Coordinator::GetComponentType()
{
	return this->_componentManager->GetComponentType<T>();
}

template<typename T>
inline std::shared_ptr<T> Coordinator::RegisterSystem()
{
	return this->_systemManager->RegisterSystem<T>();
}

template<typename T>
inline void Coordinator::SetSystemSignature(Signature signature)
{
	this->_systemManager->SetSignature<T>(signature);
}

inline void Coordinator::AddEvent(Event event)
{
	this->_eventQueue.push(event);
}

inline Event Coordinator::GetEvent()
{
	if (this->_eventQueue.empty() != true) {
		Event event = this->_eventQueue.front();
		this->_eventQueue.pop();
		return event;
	}
	return Event{Event::actions::EMPTY, 0, std::any(int(-1))};
}
