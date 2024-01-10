/*
** EPITECH PROJECT, 2023
** RType
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
 * @enum SpawnInfoType
 * @brief Enum containing the type of the SpawnInfo
 *
 */

// enum SpawnInfoType {
//     BULLET,
//     BASIC,
//     BOSS
// };

/**
 * @struct SpawnInfo
 * @brief Struct containing the SpawnInfo of an entity
 *
 */
struct SpawnInfo {
    float _x_vel;
    float _hit_w;
    float _hit_h;
    int _hp;
    int _dmg;
    float _p_end;
    float _p_vel;
    int _shoot;
};

#endif /* !SPAWNINFO_HPP_ */
