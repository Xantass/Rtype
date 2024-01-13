/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** Sprite
*/

/**
 * @struct Sprite.hpp
 * @brief File containing the Sprite struct
 *
 */
#ifndef SPRITE_HPP_
#define SPRITE_HPP_

#include <string>
#include "raylib.h"

/**
 * @struct Sprite
 * @brief Struct containing the texture of a sprite
 *
 */
struct Sprite {
    Texture2D texture; ///< Texture of the sprite
    float scale;
};

#endif /* !SPRITE_HPP_ */
