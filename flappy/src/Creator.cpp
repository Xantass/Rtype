/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** Creator
*/

#include "Creator.hpp"

Creator::Creator()
{
}

Creator::~Creator()
{
}

void Creator::createBird(Coordinator &coordinator) {
    Entity entity = coordinator.CreateEntity();
    coordinator.AddComponent<Position>(entity, {300, 300});
    coordinator.AddComponent<Velocity>(entity, {0, 0});
    coordinator.AddComponent<Falling>(entity, {true});
    coordinator.AddComponent<Hitbox2>(entity, {30, 30, 170, 120, Flappy::PLAYER});
    coordinator.AddComponent<Sprite>(entity, {Graphic::loadTexture("assets/bird.png"), 1});
}

void Creator::createBackground(Coordinator &coordinator) {
    Entity entity = coordinator.CreateEntity();
    coordinator.AddComponent<Position>(entity, {0, 0});
    coordinator.AddComponent<Sprite>(entity, {Graphic::loadTexture("assets/bg.png"), 1});
}

void Creator::createPipes(Coordinator &coordinator) {
    Entity entity = coordinator.CreateEntity();
    coordinator.AddComponent<Position>(entity, {2100, -100});
    coordinator.AddComponent<Velocity>(entity, {-0.5, 0});
    coordinator.AddComponent<Hitbox2>(entity, {0, 0, 200, 600, Flappy::WALL});
    coordinator.AddComponent<Sprite>(entity, {Graphic::loadTexture("assets/pipe-up.png"), 1});
    createCoin(coordinator);
    Entity entity2 = coordinator.CreateEntity();
    coordinator.AddComponent<Position>(entity2, {2100, 925});
    coordinator.AddComponent<Velocity>(entity2, {-0.5, 0});
    coordinator.AddComponent<Hitbox2>(entity2, {0, 0, 200, 600, Flappy::WALL});
    coordinator.AddComponent<Sprite>(entity2, {Graphic::loadTexture("assets/pipe-down.png"), 1});
}

void Creator::createCoin(Coordinator &coordinator) {
    Entity entity = coordinator.CreateEntity();
    coordinator.AddComponent<Position>(entity, {2140, 656});
    coordinator.AddComponent<Velocity>(entity, {-0.5, 0});
    coordinator.AddComponent<Hitbox2>(entity, {0, 0, 120, 112, Flappy::COIN});
    coordinator.AddComponent<Sprite>(entity, {Graphic::loadTexture("assets/coin.png"), 1});
}

void Creator::createEntities(Coordinator &coordinator) {
    createBackground(coordinator);
    createPipes(coordinator);
    createBird(coordinator);
}