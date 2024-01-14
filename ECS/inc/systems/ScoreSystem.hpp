/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** ScoreSystem
*/

/**
 * @file ScoreSystem.hpp
 * 
 * @brief File containing the Score system
 * 
 */

#ifndef SCORESYSTEM_HPP_
#define SCORESYSTEM_HPP_

#include "System.hpp"
#include "components/Score.hpp"
#include "Graphic.hpp"

/**
 * @class ScoreSystem
 * @brief Class of the Score system
 *
 */
class ScoreSystem : public System {
public:
    /**
     * @brief Update the Score system using the entities stocker in the coordinator
     * @param coordinator : The coordinator of the ECS
     *
     */
    void Update(Coordinator &coordinator);
protected:
private:
};

#include "../../src/systems/ScoreSystem.cpp"

#endif /* !SCORESYSTEM_HPP_ */
