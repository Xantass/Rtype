/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** main
*/

#include "main.hpp"

#include "Coordinator.hpp"
#include "components/Position.hpp"
#include "components/Velocity.hpp"
#include "systems/PhysicSystem.hpp"
#include "systems/NetworkServerSystem.hpp"
#include "Signature.hpp"

int main(int argc, char **argv)
{
    // Server server(12346);

    // if (!server.start()) {
    //     return -1;
    // }

    // server.loop();

    // server.closeSockets();

    Coordinator coordinator;

    coordinator.Init();

    coordinator.RegisterComponent<Position>();
    coordinator.RegisterComponent<Velocity>();

    auto physicSystem = coordinator.RegisterSystem<PhysicSystem>();
    auto networkServerSystem = coordinator.RegisterSystem<NetworkServerSystem>();

    Signature signature;

    signature.set(coordinator.GetComponentType<Position>());
    signature.set(coordinator.GetComponentType<Velocity>());
    coordinator.SetSystemSignature<PhysicSystem>(signature);
    coordinator.SetSystemSignature<NetworkServerSystem>(signature);

    Entity entity = coordinator.CreateEntity();
    coordinator.AddComponent<Position>(entity, {1, 1});
    coordinator.AddComponent<Velocity>(entity, {1, 2});

    // physicSystem->Update(coordinator);



    Entity entity2 = coordinator.CreateEntity();
    coordinator.AddComponent<Position>(entity2, {1, 1});
    coordinator.AddComponent<Velocity>(entity2, {1, 2});

    // physicSystem->Update(coordinator);

    networkServerSystem->Init();
    while (1) {
        networkServerSystem->Update(coordinator);
    }

    return 0;
}