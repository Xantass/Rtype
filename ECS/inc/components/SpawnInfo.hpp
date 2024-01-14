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
    int _seconds;
    float _y_start;
    float _y_end;
    float _y_vel;
    float _x;
    float _y;
    float width;
    float height;
    int _hp;
    int _dmg;
    int _shoot;
};

#endif /* !SPAWNINFO_HPP_ */
