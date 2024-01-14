/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** Movable
*/

/**
 * @brief File containing the Movable struct
 * 
 */

#ifndef MOVABLE_HPP_
#define MOVABLE_HPP_

/**
 * @enum Movable
 * @brief Struct containing the direction of an entity
 * 
 */
enum Direction {
    TOP, ///< Top direction
    RIGHT, ///< Right direction
    BOTTOM, ///< Bottom direction
    LEFT, ///< Left direction
    NONE ///< No direction
};

struct Movable {
    Direction direction;
};

#endif /* !MOVABLE_HPP_ */
