/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** main
*/

#include <memory>
#include "main.hpp"
#include "../../ECS/ECS.hpp"
#include "../../ECS/inc/systems/NetworkServerSystem.hpp"

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
        networkServerSystem->Update(coordinator);
        if (elapsedTime >= interval) {
            physicSystem->Update(coordinator);
            startTime = currentTime;
        }
    }
    return 0;
}