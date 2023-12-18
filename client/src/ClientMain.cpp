/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** ClientMain
*/

#include "ClientMain.hpp"
#include "Coordinator.hpp"
#include "components/Position.hpp"
#include "components/Velocity.hpp"
#include "systems/PhysicSystem.hpp"
#include "systems/NetworkClientSystem.hpp"
#include "Signature.hpp"

int main()
{
    Coordinator coordinator;

    coordinator.Init();

    coordinator.RegisterComponent<Position>();
    coordinator.RegisterComponent<Velocity>();

    auto physicSystem = coordinator.RegisterSystem<PhysicSystem>();
    auto networkClientSystem = coordinator.RegisterSystem<NetworkClientSystem>();

    Signature signature;

    signature.set(coordinator.GetComponentType<Position>());
    signature.set(coordinator.GetComponentType<Velocity>());
    coordinator.SetSystemSignature<PhysicSystem>(signature);
    coordinator.SetSystemSignature<NetworkClientSystem>(signature);

    Entity entity = coordinator.CreateEntity();
    coordinator.AddComponent<Position>(entity, {1, 1});
    coordinator.AddComponent<Velocity>(entity, {1, 2});

    // physicSystem->Update(coordinator);

    Entity entity2 = coordinator.CreateEntity();
    coordinator.AddComponent<Position>(entity2, {1, 1});
    coordinator.AddComponent<Velocity>(entity2, {1, 2});

    // physicSystem->Update(coordinator);

    networkClientSystem->Init();
    while (1) {
        networkClientSystem->Update(coordinator);
    }
    return 0;
}