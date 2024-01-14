/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** Damage.hpp
*/

/**
 * @file Damage.hpp
 * @brief File containing the Damage struct
 *
 */

#ifndef DAMAGE_HPP_
#define DAMAGE_HPP_

/**
 * @struct Damage
 * @brief Struct containing the damage of an entity
 *
 */
struct Damage {
    int _max_dmg; ///< Max damage that the entity can do
    int _curr_dmg; ///< Current damage that the entity do
};

#endif /* !DAMAGE_HPP_ */
