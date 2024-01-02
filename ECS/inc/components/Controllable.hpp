/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** Controllable.hpp
*/

/**
 * @file Controllable.hpp
 * @brief File containing the Controllable struct
 *
 */

#ifndef CONTROLLABLE_HPP_
#define CONTROLLABLE_HPP_

/**
 * @enum ControllableType
 * @brief Enum containing the type of the controllable
 *
 */
enum ControllableType {
    INPUT,
    IA,
    ENGINE
};

/**
 * @struct Controllable
 * @brief Struct containing the ControllableType of an entity
 *
 */
struct Controllable {
    ControllableType type; ///< Type of the controllable
};

#endif /* !CONTROLLABLE_HPP_ */
