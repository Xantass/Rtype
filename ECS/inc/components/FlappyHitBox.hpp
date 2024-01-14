/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** Hitbox
*/

/**
 * @file FlappyHitbox.hpp
 * @brief File containing the Hitbox struct
 *
 */

#ifndef FLAPPYHITBOX_HPP_
#define FLAPPYHITBOX_HPP_
namespace Flappy {
    /**
     * @enum HitboxType
     * @brief Enum containing the type of the hitbox
     *
     */
    enum HitboxType {
        PLAYER, ///< Player
        WALL, ///< Wall
        COIN, ///< Coin
    };
}

/**
 * @struct Hitbox
 * @brief Struct containing the hitbox of an entity
 *
 */
struct Hitbox2 {
    float _x; ///< X difference with the entity position
    float _y; ///< Y difference with the entity position
    float width; ///< Width of the hitbox
    float height; ///< Height of the hitbox
    Flappy::HitboxType type; ///< Type of the hitbox
};
#endif /* !HITBOX_HPP_ */
