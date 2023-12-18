/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** ClientMain
*/

#include "Coordinator.hpp"
#include "components/Position.hpp"
#include "components/Velocity.hpp"
#include "components/Sprite.hpp"
#include "systems/PhysicSystem.hpp"
#include "systems/GraphicalSystem.hpp"
#include "Signature.hpp"
#include "raylib.h"

int main(int argc, char **argv)
{
    // Server server(12346);

    // if (!server.start()) {
    //     return -1;
    // }

    // server.loop();

    // server.closeSockets();

    InitWindow(800, 600, "Big test");
    Coordinator coordinator;

    coordinator.Init();

    coordinator.RegisterComponent<Position>();
    coordinator.RegisterComponent<Velocity>();
    coordinator.RegisterComponent<Sprite>();

    auto physicSystem = coordinator.RegisterSystem<PhysicSystem>();
    auto graphicSystem = coordinator.RegisterSystem<GraphicalSystem>();

    Signature signature;

    signature.set(coordinator.GetComponentType<Position>());
    signature.set(coordinator.GetComponentType<Velocity>());
    coordinator.SetSystemSignature<PhysicSystem>(signature);

    Signature signature2;

    signature2.set(coordinator.GetComponentType<Position>());
    signature2.set(coordinator.GetComponentType<Sprite>());
    coordinator.SetSystemSignature<GraphicalSystem>(signature2);

    Entity entity = coordinator.CreateEntity();
    coordinator.AddComponent<Position>(entity, {1, 1});
    coordinator.AddComponent<Velocity>(entity, {1, 2});
    coordinator.AddComponent<Sprite>(entity, {LoadTexture("assets/horizon.png")});


    Entity entity2 = coordinator.CreateEntity();
    coordinator.AddComponent<Position>(entity2, {1, 1});
    coordinator.AddComponent<Velocity>(entity2, {1, -2});
    coordinator.AddComponent<Sprite>(entity, {LoadTexture("assets/horizon.png")});
    while (!WindowShouldClose()) {
        // physicSystem->Update(coordinator);
        BeginDrawing();
        graphicSystem->Update(coordinator);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}