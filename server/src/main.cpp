/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** main
*/

#include <memory>
#include "main.hpp"
#include "Coordinator.hpp"
#include "components/Position.hpp"
#include "components/Velocity.hpp"
#include "components/Hitbox.hpp"
#include "systems/PhysicSystem.hpp"
#include "systems/NetworkServerSystem.hpp"
#include "Signature.hpp"

int main(int argc, char **argv)
{
    Coordinator coordinator;

    coordinator.Init();

    coordinator.RegisterComponent<Position>();
    coordinator.RegisterComponent<Velocity>();
    coordinator.RegisterComponent<Hitbox>();

    auto physicSystem = coordinator.RegisterSystem<PhysicSystem>();
    auto networkServerSystem = coordinator.RegisterSystem<NetworkServerSystem>();

    Signature signature;

    signature.set(coordinator.GetComponentType<Position>());
    signature.set(coordinator.GetComponentType<Velocity>());
    signature.set(coordinator.GetComponentType<Hitbox>());
    coordinator.SetSystemSignature<PhysicSystem>(signature);
    coordinator.SetSystemSignature<NetworkServerSystem>(signature);

    Entity entity = coordinator.CreateEntity();
    coordinator.AddComponent<Position>(entity, {1, 0});
    coordinator.AddComponent<Velocity>(entity, {0, 0});
    coordinator.AddComponent<Hitbox>(entity, {0, 0, 1, 1, PLAYER});

    physicSystem->Update(coordinator);

    Entity entity2 = coordinator.CreateEntity();
    coordinator.AddComponent<Position>(entity2, {0, 0});
    coordinator.AddComponent<Velocity>(entity2, {1, 0});
    coordinator.AddComponent<Hitbox>(entity2, {0, 0, 1, 1, ENNEMY});

    physicSystem->Update(coordinator);

    networkServerSystem->Init();
    while (1) {
        networkServerSystem->Update(coordinator);
    }

    return 0;
}