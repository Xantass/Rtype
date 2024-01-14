/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** Main
*/

#include "Creator.hpp"

int main(int ac, char **av) {
    (void)ac;
    (void)av;
    Coordinator coordinator;

    coordinator.Init();
    coordinator.RegisterComponent<Position>();
    coordinator.RegisterComponent<Velocity>();
    coordinator.RegisterComponent<Sprite>();
    coordinator.RegisterComponent<Falling>();
    coordinator.RegisterComponent<Hitbox2>();
    // coordinator.RegisterComponent<Hitbox>();
    auto physicSystem = coordinator.RegisterSystem<PhysicSystem>();
    auto graphicSystem = coordinator.RegisterSystem<GraphicSystem>();
    auto gravitySystem = coordinator.RegisterSystem<GravitySystem>();
    auto collisionSystem = coordinator.RegisterSystem<CollisionSystem2>();

    Signature signature;
    signature.set(coordinator.GetComponentType<Position>());
    signature.set(coordinator.GetComponentType<Sprite>());
    coordinator.SetSystemSignature<GraphicSystem>(signature);
    Signature signature2;
    signature2.set(coordinator.GetComponentType<Position>());
    signature2.set(coordinator.GetComponentType<Velocity>());
    coordinator.SetSystemSignature<PhysicSystem>(signature2);
    Signature signature3;
    signature3.set(coordinator.GetComponentType<Velocity>());
    signature3.set(coordinator.GetComponentType<Falling>());
    coordinator.SetSystemSignature<GravitySystem>(signature3);
    Signature signature4;
    signature4.set(coordinator.GetComponentType<Position>());
    signature4.set(coordinator.GetComponentType<Velocity>());
    signature4.set(coordinator.GetComponentType<Hitbox2>());
    coordinator.SetSystemSignature<CollisionSystem2>(signature4);

    Graphic::init(1920, 1080, "Flappy Bird");
    Graphic::toggleFullScreen();
    Creator creator;
    creator.createEntities(coordinator);
    while (!Graphic::shouldCloseWindow()) {
        Graphic::beginDrawing();
        Graphic::clearBackground(BLACK);
        graphicSystem->Update(coordinator);
        physicSystem->Update(coordinator);
        gravitySystem->Update(coordinator);
        collisionSystem->Update(coordinator);
        Graphic::endDrawing();
    }
    Graphic::close();
    return 0;
}
