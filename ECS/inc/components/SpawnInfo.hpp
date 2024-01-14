/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** SpawnInfo.hpp
*/

/**
 * @file SpawnInfo.hpp
 * @brief File containing the SpawnInfo struct
 *
 */

#ifndef SPAWNINFO_HPP_
#define SPAWNINFO_HPP_

/**
 * @struct SpawnInfo
 * @brief Struct containing the SpawnInfoType of an entity
 *
 */
struct SpawnInfo {
    int _seconds; ///< Seconds before the entity spawn
    float _y_start; ///< Y position where the entity spawn
    float _y_end; ///< Y position where the entity stop
    float _y_vel; ///< Y velocity of the entity
    float _x; ///< X position of the entity
    float _y; ///< Y position of the entity
    float width; ///< Width of the entity
    float height; ///< Height of the entity
    int _hp; ///< HealthPoints of the entity
    int _dmg; ///< Damage of the entity 
    int _shoot; ///< Shoot of the entity
};

#endif /* !SPAWNINFO_HPP_ */
