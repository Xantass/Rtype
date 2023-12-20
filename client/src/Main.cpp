/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** Main
*/

#include "Client.cpp"
#include "Coordinator.hpp"
#include "components/Position.hpp"
#include "components/Velocity.hpp"
#include "components/Sprite.hpp"
#include "components/Hitbox.hpp"
#include "systems/PhysicSystem.hpp"
#include "systems/GraphicalSystem.hpp"
#include "systems/ParallaxSystem.hpp"
#include "systems/MovableSystem.hpp"
#include "systems/NetworkClientSystem.hpp"
#include "Signature.hpp"

int main(int ac, char **av)
{
    Client client("127.0.0.1", "4242");
    Coordinator coordinator;

    coordinator.Init();
    client.initWindow(1920, 1080, "R-Type");

    coordinator.RegisterComponent<Position>();
    coordinator.RegisterComponent<Velocity>();
    coordinator.RegisterComponent<Sprite>();
    coordinator.RegisterComponent<Hitbox>();
    coordinator.RegisterComponent<Movable>();

    auto physicSystem = coordinator.RegisterSystem<PhysicSystem>();
    auto graphicSystem = coordinator.RegisterSystem<GraphicalSystem>();
    auto parallaxSystem = coordinator.RegisterSystem<ParallaxSystem>();
    auto movableSystem = coordinator.RegisterSystem<MovableSystem>();
    auto networkClientSystem = coordinator.RegisterSystem<NetworkClientSystem>();

    Signature signature;

    signature.set(coordinator.GetComponentType<Position>());
    signature.set(coordinator.GetComponentType<Sprite>());
    coordinator.SetSystemSignature<ParallaxSystem>(signature);

    Signature signature2;

    signature2.set(coordinator.GetComponentType<Position>());
    signature2.set(coordinator.GetComponentType<Velocity>());
    signature2.set(coordinator.GetComponentType<Sprite>());
    coordinator.SetSystemSignature<GraphicalSystem>(signature2);

    Signature signature3;

    signature3.set(coordinator.GetComponentType<Position>());
    signature3.set(coordinator.GetComponentType<Velocity>());
    signature3.set(coordinator.GetComponentType<Hitbox>());
    coordinator.SetSystemSignature<PhysicSystem>(signature3);
    coordinator.SetSystemSignature<NetworkClientSystem>(signature3);

    Signature signature4;

    signature4.set(coordinator.GetComponentType<Movable>());
    signature4.set(coordinator.GetComponentType<Velocity>());
    coordinator.SetSystemSignature<MovableSystem>(signature4);


    Entity entity2 = coordinator.CreateEntity();
    coordinator.AddComponent<Position>(entity2, {1920, 0});
    coordinator.AddComponent<Velocity>(entity2, {-2, 0});
    coordinator.AddComponent<Hitbox>(entity2, {0, 0, 0, 0, OTHER});
    coordinator.AddComponent<Sprite>(entity2, {LoadTexture("assets/parallax-space-big-planet.png")});

    Entity entity3 = coordinator.CreateEntity();
    coordinator.AddComponent<Position>(entity3, {1920, 0});
    coordinator.AddComponent<Velocity>(entity3, {-2.3, 0});
    coordinator.AddComponent<Hitbox>(entity3, {0, 0, 0, 0, OTHER});
    coordinator.AddComponent<Sprite>(entity3, {LoadTexture("assets/parallax-space-far-planets.png")});

    Entity entity4 = coordinator.CreateEntity();
    coordinator.AddComponent<Position>(entity4, {1920, 0});
    coordinator.AddComponent<Velocity>(entity4, {-2.6, 0});
    coordinator.AddComponent<Hitbox>(entity4, {0, 0, 0, 0, OTHER});
    coordinator.AddComponent<Sprite>(entity4, {LoadTexture("assets/parallax-space-ring-planet.png")});

    Entity entity5 = coordinator.CreateEntity();
    coordinator.AddComponent<Position>(entity5, {1920, 0});
    coordinator.AddComponent<Velocity>(entity5, {-2.9, 0});
    coordinator.AddComponent<Hitbox>(entity5, {0, 0, 0, 0, OTHER});
    coordinator.AddComponent<Sprite>(entity5, {LoadTexture("assets/parallax-space-stars.png")});

    Entity entity = coordinator.CreateEntity();
    coordinator.AddComponent<Position>(entity, {400, 400});
    coordinator.AddComponent<Velocity>(entity, {0, 0});
    coordinator.AddComponent<Hitbox>(entity, {0, 0, 0, 0, OTHER});
    coordinator.AddComponent<Movable>(entity, {NONE});
    coordinator.AddComponent<Sprite>(entity, {LoadTexture("assets/planet.png")});

    networkClientSystem->Init(coordinator);

    while (!client.shouldCloseWindow()) {
        BeginDrawing();
        ClearBackground(BLACK);
        movableSystem->Update(coordinator);
        physicSystem->Update(coordinator);
        parallaxSystem->Update(coordinator);
        graphicSystem->Update(coordinator);
        networkClientSystem->Update(coordinator);
        EndDrawing();
    }
    client.destroyWindow();
    return 0;
}