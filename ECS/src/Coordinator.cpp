/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** Coordinator
*/

#include "systems/PhysicSystem.hpp"

void Coordinator::Init()
{
	this->_componentManager = std::make_unique<ComponentManager>();
	this->_entityManager = std::make_unique<EntityManager>();
	this->_systemManager = std::make_unique<SystemManager>();
}

Entity Coordinator::CreateEntity()
{
	return this->_entityManager->CreateEntity();
}

void Coordinator::DestroyEntity(Entity entity)
{
	this->_entityManager->DestroyEntity(entity);
	this->_componentManager->EntityDestroyed(entity);
	this->_systemManager->EntityDestroyed(entity);
}

template<typename T>
void Coordinator::RegisterComponent()
{
	this->_componentManager->RegisterComponent<T>();
}

template<typename T>
void Coordinator::AddComponent(Entity entity, T component)
{
	auto signature = this->_entityManager->GetSignature(entity);

	this->_componentManager->AddComponent<T>(entity, component);
	signature.set(this->_componentManager->GetComponentType<T>(), true);
	this->_entityManager->SetSignature(entity, signature);
	this->_systemManager->EntitySignatureChanged(entity, signature);
}

template<typename T>
void Coordinator::RemoveComponent(Entity entity)
{
	auto signature = this->_entityManager->GetSignature(entity);

	this->_componentManager->RemoveComponent<T>(entity);
	signature.set(this->_componentManager->GetComponentType<T>(), false);
	this->_entityManager->SetSignature(entity, signature);
	this->_systemManager->EntitySignatureChanged(entity, signature);
}

template<typename T>
T& Coordinator::GetComponent(Entity entity)
{
	return this->_componentManager->GetComponent<T>(entity);
}

template<typename T>
ComponentType Coordinator::GetComponentType()
{
	return this->_componentManager->GetComponentType<T>();
}

template<typename T>
std::shared_ptr<T> Coordinator::RegisterSystem()
{
	return this->_systemManager->RegisterSystem<T>();
}

template<typename T>
void Coordinator::SetSystemSignature(Signature signature)
{
	this->_systemManager->SetSignature<T>(signature);
}

//this is here to prevent the compiler being mad about templates.
//Components
template void Coordinator::RegisterComponent<Position>();
template void Coordinator::RegisterComponent<Velocity>();
template void Coordinator::AddComponent<Position>(Entity entity, Position component);
template void Coordinator::AddComponent<Velocity>(Entity entity, Velocity component);
template void Coordinator::RemoveComponent<Position>(Entity entity);
template void Coordinator::RemoveComponent<Velocity>(Entity entity);
template Position& Coordinator::GetComponent<Position>(Entity entity);
template Velocity& Coordinator::GetComponent<Velocity>(Entity entity);
template ComponentType Coordinator::GetComponentType<Position>();
template ComponentType Coordinator::GetComponentType<Velocity>();
//Systems
template std::shared_ptr<PhysicSystem> Coordinator::RegisterSystem<PhysicSystem>();
template void Coordinator::SetSystemSignature<PhysicSystem>(Signature signature);
