/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** FlappyCollisionSystem
*/

#include <cstdlib>
#include <ctime>
#include "FlappyCollisionSystem.hpp"
#include "ECSFlappy.hpp"

inline void CollisionSystem2::Update(Coordinator &coordinator) {
    for (auto entity : this->_entities) {
        auto& pos = coordinator.GetComponent<Position>(entity);
        auto& hit = coordinator.GetComponent<Hitbox2>(entity);
        if (hit.type == Flappy::PLAYER) {
            if (pos._y < 0) {
                pos._y = 0;
            }
            if (pos._y + 150 > 1080) {
                pos._y = 930;
            }
        }
        if (hit.type == Flappy::WALL) {
            if (pos._x + 200 <= 0) {
                std::srand(static_cast<unsigned>(std::time(nullptr)));
                float randomNumber = std::rand() % 501 - 500;
                auto& pos1 = coordinator.GetComponent<Position>(entity + 1);
                auto& sprite = coordinator.GetComponent<Sprite>(entity + 1);
                auto& pos2 = coordinator.GetComponent<Position>(entity + 2);
                pos = {2000, randomNumber};
                pos1 = {2040, randomNumber + 756};
                pos2 = {2000, randomNumber + 1025};
                sprite.scale = 1;
            }
        }
        for (auto comp : this->_entities) {
            if (entity == comp)
                continue;
            auto& c_pos = coordinator.GetComponent<Position>(comp);
            auto& sprite = coordinator.GetComponent<Sprite>(comp);
            auto& c_hit = coordinator.GetComponent<Hitbox2>(comp);
            if (hit.type == Flappy::PLAYER && c_hit.type == Flappy::COIN && sprite.scale == 1) {
                if (pos._x + hit._x + hit.width >= c_pos._x + c_hit._x &&
                    pos._x + hit._x <= c_pos._x + c_hit._x + c_hit.width &&
                    pos._y + hit._y + hit.height >= c_pos._y + c_hit._y &&
                    pos._y + hit._y <= c_pos._y + c_hit._y + c_hit.height) {
                    auto& sound = coordinator.GetComponent<Son>(comp);
                    auto& score = coordinator.GetComponent<Score>(comp);
                    sprite.scale = 0;
                    sound.shouldBePlayed = true;
                    score.score++;
                }
            }
            if (hit.type == Flappy::PLAYER && c_hit.type == Flappy::WALL) {
                if (pos._x + hit._x + hit.width >= c_pos._x + c_hit._x &&
                    pos._x + hit._x <= c_pos._x + c_hit._x + c_hit.width &&
                    pos._y + hit._y + hit.height >= c_pos._y + c_hit._y &&
                    pos._y + hit._y <= c_pos._y + c_hit._y + c_hit.height) {
                    for (auto entity : this->_entities) {
                        auto& vel = coordinator.GetComponent<Velocity>(entity);
                        vel = {0, 0};
                    }
                }
            }
        }
    }
}