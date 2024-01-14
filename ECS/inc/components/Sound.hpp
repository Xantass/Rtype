/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** Sound
*/

/**
 * @file Sound.hpp
 * @brief File containing the Sound struct
 *
 */
#ifndef SOUND_HPP_
#define SOUND_HPP_

#include "Graphic.hpp"

/**
 * @brief Struct containing the sound of an entity
 *
 */
struct Son {
    Sound sound; ///< Sound of an entity
    bool shouldBePlayed; ///< Bool showing if the sound should be played
};

#endif /* !SOUND_HPP_ */
