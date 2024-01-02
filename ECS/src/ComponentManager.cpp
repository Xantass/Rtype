/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** ComponentManager
*/

#include "ComponentManager.hpp"

template<typename T>
void ComponentManager::RegisterComponent()
{
	std::type_index typeName = std::type_index(typeid(T));

	// if (this->_componentTypes.find(typeName) == this->_componentTypes.end()) {
		// ERROR : "Registering component type more than once."
	// }
	// Add this component type to the component type map
	this->_componentTypes.insert({typeName, this->_nextComponentType});
	// Create a ComponentArray pointer and add it to the component arrays map
	this->_componentArrays.insert({typeName, std::make_shared<ComponentArray<T>>()});
	// Increment the value so that the next component registered will be different
	this->_nextComponentType++;
}

template<typename T>
ComponentType ComponentManager::GetComponentType()
{
	std::type_index typeName = std::type_index(typeid(T));

	// if (this->_componentTypes.find(typeName) == this->_componentTypes.end()) {
		// ERROR : "Component not registered before use."
	// }
	// Return this component's type - used for creating signatures
	return this->_componentTypes[typeName];
}

template<typename T>
void ComponentManager::AddComponent(Entity entity, T component)
{
	GetComponentArray<T>()->InsertData(entity, component);
}

template<typename T>
void ComponentManager::RemoveComponent(Entity entity)
{
	GetComponentArray<T>()->RemoveData(entity);
}

template<typename T>
T& ComponentManager::GetComponent(Entity entity)
{
	return GetComponentArray<T>()->GetData(entity);
}

void ComponentManager::EntityDestroyed(Entity entity)
{
	for (auto const& pair : this->_componentArrays) {
		auto const& component = pair.second;
		component->EntityDestroyed(entity);
	}
}
