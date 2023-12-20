/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** Coordinator
*/

#include "systems/PhysicSystem.hpp"
#include "systems/GraphicalSystem.hpp"
#include "systems/ParallaxSystem.hpp"
#include "systems/MovableSystem.hpp"
#include "systems/NetworkServerSystem.hpp"

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
template void Coordinator::RegisterComponent<Hitbox>();
template void Coordinator::RegisterComponent<Sprite>();
template void Coordinator::RegisterComponent<Movable>();
template void Coordinator::AddComponent<Position>(Entity entity, Position component);
template void Coordinator::AddComponent<Velocity>(Entity entity, Velocity component);
template void Coordinator::AddComponent<Hitbox>(Entity entity, Hitbox component);
template void Coordinator::AddComponent<Sprite>(Entity entity, Sprite component);
template void Coordinator::AddComponent<Movable>(Entity entity, Movable component);
template void Coordinator::RemoveComponent<Position>(Entity entity);
template void Coordinator::RemoveComponent<Velocity>(Entity entity);
template void Coordinator::RemoveComponent<Hitbox>(Entity entity);
template void Coordinator::RemoveComponent<Sprite>(Entity entity);
template void Coordinator::RemoveComponent<Movable>(Entity entity);
template Position& Coordinator::GetComponent<Position>(Entity entity);
template Velocity& Coordinator::GetComponent<Velocity>(Entity entity);
template Hitbox& Coordinator::GetComponent<Hitbox>(Entity entity);
template Sprite& Coordinator::GetComponent<Sprite>(Entity entity);
template Movable& Coordinator::GetComponent<Movable>(Entity entity);
template ComponentType Coordinator::GetComponentType<Position>();
template ComponentType Coordinator::GetComponentType<Velocity>();
template ComponentType Coordinator::GetComponentType<Hitbox>();
template ComponentType Coordinator::GetComponentType<Sprite>();
template ComponentType Coordinator::GetComponentType<Movable>();
//Systems
template std::shared_ptr<PhysicSystem> Coordinator::RegisterSystem<PhysicSystem>();
template std::shared_ptr<GraphicalSystem> Coordinator::RegisterSystem<GraphicalSystem>();
template std::shared_ptr<ParallaxSystem> Coordinator::RegisterSystem<ParallaxSystem>();
template std::shared_ptr<MovableSystem> Coordinator::RegisterSystem<MovableSystem>();
template std::shared_ptr<NetworkServerSystem> Coordinator::RegisterSystem<NetworkServerSystem>();
template void Coordinator::SetSystemSignature<PhysicSystem>(Signature signature);
template void Coordinator::SetSystemSignature<ParallaxSystem>(Signature signature);
template void Coordinator::SetSystemSignature<GraphicalSystem>(Signature signature);
template void Coordinator::SetSystemSignature<MovableSystem>(Signature signature);
template void Coordinator::SetSystemSignature<NetworkServerSystem>(Signature signature);