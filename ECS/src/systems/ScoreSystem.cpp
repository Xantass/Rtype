/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** ScoreSystem
*/

#include "ScoreSystem.hpp"

inline void ScoreSystem::Update(Coordinator &coordinator)
{
    for (auto entity : this->_entities) {
        auto& score = coordinator.GetComponent<Score>(entity);

        Graphic::drawText("Score: " + std::to_string(score.score), 30, 30, 70, RWHITE);
    }
}
