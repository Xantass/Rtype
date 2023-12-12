/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** System
*/

#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_

#include <set>

#include "Entity.hpp"

class System {
public:
	std::set<Entity> mEntities;
};

#endif /* !SYSTEM_HPP_ */
