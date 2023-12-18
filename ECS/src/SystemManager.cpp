/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** SystemManager
*/

#include "systems/PhysicSystem.hpp"

template<typename T>
std::shared_ptr<T> SystemManager::RegisterSystem()
{
	std::type_index typeName = std::type_index(typeid(T));

	// if (this->_systems[typeName] == this->_systems[this->_systems.end()]) {
	//	ERROR : "Registering system more than once."
	// }
	// Create a pointer to the system and return it so it can be used externally
	auto system = std::make_shared<T>();
	this->_systems.insert({typeName, system});
	return system;
}

template<typename T>
void SystemManager::SetSignature(Signature signature)
{
    std::type_index typeName = typeid(T);

	// if (this->_systems[typeName] == this->_systems.end()) {
		// ERROR : "System used before registered."
	// }
	_signatures.insert({typeName, signature});
}

void SystemManager::EntityDestroyed(Entity entity)
{
	for (auto const& pair : this->_systems) {
		auto const& system = pair.second;
		system->_entities.erase(entity);
	}
}

void SystemManager::EntitySignatureChanged(Entity entity, Signature entitySignature)
{
	// Notify each system that an entity's signature changed
	for (auto const& pair : this->_systems) {
		auto const& type = pair.first;
		auto const& system = pair.second;
		auto const& systemSignature = this->_signatures[type];
		if ((entitySignature & systemSignature) == systemSignature) 
			system->_entities.insert(entity); // Entity signature matches system signature - insert into set
		else
			system->_entities.erase(entity); // Entity signature does not match system signature - erase from set
	}
}

template std::shared_ptr<PhysicSystem> SystemManager::RegisterSystem<PhysicSystem>();
template void SystemManager::SetSignature<PhysicSystem>(Signature signature);