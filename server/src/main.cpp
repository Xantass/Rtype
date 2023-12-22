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
#include "Event.hpp"

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

    networkServerSystem->Init();
    std::chrono::milliseconds interval(10);
    std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();
    std::chrono::steady_clock::duration elapsedTime;
    while (1) {
        currentTime = std::chrono::steady_clock::now();
        elapsedTime = currentTime - startTime;
        if (elapsedTime >= interval) {
            networkServerSystem->Update(coordinator);
            physicSystem->Update(coordinator);
            startTime = currentTime;
        }
    }
    return 0;
}