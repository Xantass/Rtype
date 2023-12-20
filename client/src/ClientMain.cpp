/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** ClientMain
*/

#include <memory>
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
    coordinator.RegisterComponent<Hitbox>();

    auto physicSystem = coordinator.RegisterSystem<PhysicSystem>();
    auto networkClientSystem = coordinator.RegisterSystem<NetworkClientSystem>();

    Signature signature;

    signature.set(coordinator.GetComponentType<Position>());
    signature.set(coordinator.GetComponentType<Velocity>());
    signature.set(coordinator.GetComponentType<Hitbox>());
    coordinator.SetSystemSignature<PhysicSystem>(signature);
    coordinator.SetSystemSignature<NetworkClientSystem>(signature);

    networkClientSystem->Init(coordinator);
    while (1) {
        networkClientSystem->Update(coordinator);
    }
    return 0;
}