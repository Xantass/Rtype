/*
** EPITECH PROJECT, 2023
** RType
** File description:
** SpawnClock.hpp
*/

/**
 * @file SpawnClock.hpp
 * @brief File containing the SpawnClock struct
 *
 */

#ifndef SPAWNCLOCK_HPP_
#define SPAWNCLOCK_HPP_

#include <chrono>

/**
 * @enum SpawnClockType
 * @brief Enum containing the type of the SpawnClock
 *
 */

/**
 * @struct SpawnClock
 * @brief Struct containing the SpawnClockType of an entity
 *
 */
struct SpawnClock {
    std::chrono::high_resolution_clock::time_point _spawn_point; ///<
    std::chrono::high_resolution_clock::time_point _spawn_end;
};

#endif /* !SPAWNCLOCK_HPP_ */
