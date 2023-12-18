/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** EntityManager
*/

/**
 * @file EntityManager.hpp
 * @brief File containing the EntityManager class
 * 
 */

#ifndef ENTITYMANAGER_HPP_
#define ENTITYMANAGER_HPP_

#include <queue>
#include <array>

#include "Signature.hpp"
#include "Entity.hpp"

/**
 * @class EntityManager
 * @brief Class of the entity manager
 * 
 */
class EntityManager {
	public:
	    EntityManager();
	    ~EntityManager();
		/**
		 * @brief Create a Entity object
		 * 
		 * @return Entity 
		 */
		Entity CreateEntity();
		/**
		 * @brief Destroy an entity
		 * 
		 * @param entity Entity to be destroyed
		 */
		void DestroyEntity(Entity entity);
		/**
		 * @brief Set the Signature object
		 * @details The signature is a bitset that contains the components of the entity. If the entity has the components 0, 1 and 3, the signature will be 1011.
		 * 
		 * 
		 * @param entity Entity to set the signature to
		 * @param signature Signature to set
		 */
		void SetSignature(Entity entity, Signature signature);
		/**
		 * @brief Get the Signature object
		 * 
		 * @param entity Entity to get the signature from
		 * @return Signature Signature of the entity
		 */
		Signature GetSignature(Entity entity);
	protected:
	private:
	/**
	 * @brief Queue of available entities
	 * 
	 */
	std::queue<Entity> _availableEntities{};
	/**
	 * @brief Number of living entities
	 * 
	 */
	uint32_t _livingEntityCount{};
	/**
	 * @brief Array of signatures
	 * 
	 */
	std::array<Signature, MAX_ENTITIES> _signatures{};
};

#endif /* !ENTITYMANAGER_HPP_ */
