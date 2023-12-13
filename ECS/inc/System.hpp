/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** System
*/

/**
 * @file System.hpp
 * @brief File containing the System class
 * 
 */

#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_

#include <set>

#include "Entity.hpp"

/**
 * @class System
 * @brief Class of the system
 * 
 */
class System {
public:

	/**
	 * @brief Entities list
	 * 
	 */
	std::set<Entity> _entities;
};

#endif /* !SYSTEM_HPP_ */
