/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** HealthPoint.hpp
*/

/**
 * @file HealthPoint.hpp
 * @brief File containing the HealthPoint struct
 *
 */

#ifndef HEALTH_POINT_HPP_
#define HEALTH_POINT_HPP_

/**
 * @struct HealthPoint
 * @brief Struct containing the HealthPoints of an entity
 *
 */
struct HealthPoint {
    int _max_hp; ///< Max HealthPoints that the entity can have
    int _curr_hp; ///< Current HealthPoints that the entity have
};

#endif /* !HEALTH_POINT_HPP_ */
