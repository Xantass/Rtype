/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** SystemManager
*/

/**
 * @file SystemManager.hpp
 * @brief File containing the SystemManager class
 * 
 */

#ifndef SYSTEMMANAGER_HPP_
#define SYSTEMMANAGER_HPP_

#include <memory>
#include <unordered_map>
#include <typeindex>

#include "Entity.hpp"
#include "Signature.hpp"
#include "System.hpp"

/**
 * @class SystemManager
 * @brief Class of the system manager
 * 
 */
class SystemManager {
public:
	/**
	 * @brief Register a new system
	 * 
	 * @tparam T Type of the system
	 * @return std::shared_ptr<T> Pointer to the system
	 */
	template<typename T>
	std::shared_ptr<T> RegisterSystem();

	/**
	 * @brief Set the Signature object
	 * @details The signature is a bitset that contains the components of the system. If the system has the components 0, 1 and 3, the signature will be 1011.
	 * 
	 * @tparam T Type of the system
	 * @param signature Signature to set
	 */
	template<typename T>
	void SetSignature(Signature signature);

	/**
	 * @brief Called when an entity is destroyed so that the system manager can update its references
	 * 
	 * @param entity Entity to be destroyed
	 */
	void EntityDestroyed(Entity entity);

	/**
	 * @brief Called when a component is added to an entity so that the system manager can update its references
	 * 
	 * @param entity Entity to add the component to
	 * @param entitySignature Signature of the entity
	 */
	void EntitySignatureChanged(Entity entity, Signature entitySignature);

private:
	/**
	 * @brief Map to store the signatures of the systems registered
	 * 
	 */
	std::unordered_map<std::type_index, Signature> _signatures{};

	/**
	 * @brief Map to store the systems registered
	 * 
	 */
	std::unordered_map<std::type_index, std::shared_ptr<System>> _systems{};
};

#include "../src/SystemManager.cpp"

#endif /* !SYSTEMMANAGER_HPP_ */
