/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** Hitbox
*/

/**
 * @file Hitbox.hpp
 * @brief File containing the Hitbox struct
 *
 */

#ifndef HITBOX_HPP_
#define HITBOX_HPP_

/**
 * @enum HitboxType
 * @brief Enum containing the type of the hitbox
 *
 */
enum HitboxType {
    ENNEMY,
    PLAYER
};

/**
 * @struct Hitbox
 * @brief Struct containing the hitbox of an entity
 *
 */
struct Hitbox {
    float x; ///< X difference with the entity position
    float y; ///< Y difference with the entity position
    float width; ///< Width of the hitbox
    float height; ///< Height of the hitbox
    HitboxType type; ///< Type of the hitbox
};

#endif /* !HITBOX_HPP_ */
