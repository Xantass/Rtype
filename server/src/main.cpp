/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** main
*/

#include <memory>
#include "main.hpp"
#include "../../ECS/ECSServer.hpp"

int main(int argc, char **argv)
{
    Coordinator coordinator;

    coordinator.Init();

    coordinator.RegisterComponent<Position>();
    coordinator.RegisterComponent<Velocity>();
    coordinator.RegisterComponent<Hitbox>();
    coordinator.RegisterComponent<Controllable>();
    coordinator.RegisterComponent<SpawnClock>();

    auto physicSystem = coordinator.RegisterSystem<PhysicSystem>();
    auto controlSystem = coordinator.RegisterSystem<ControlSystem>();
    auto networkServerSystem = coordinator.RegisterSystem<NetworkServerSystem>();
    auto spawnSystem = coordinator.RegisterSystem<SpawnSystem>();
    
    Signature signature;

    signature.set(coordinator.GetComponentType<Position>());
    signature.set(coordinator.GetComponentType<Velocity>());
    signature.set(coordinator.GetComponentType<Hitbox>());
    coordinator.SetSystemSignature<PhysicSystem>(signature);
    coordinator.SetSystemSignature<NetworkServerSystem>(signature);
    
    Signature signature2;

    signature2.set(coordinator.GetComponentType<Position>());
    signature2.set(coordinator.GetComponentType<Velocity>());
    signature2.set(coordinator.GetComponentType<Controllable>());
    coordinator.SetSystemSignature<ControlSystem>(signature2);

    Signature signature3;
    
    signature3.set(coordinator.GetComponentType<SpawnClock>());
    coordinator.SetSystemSignature<SpawnClock>(signature3);

    Entity ent = coordinator.CreateEntity();
    coordinator.AddComponent<SpawnClock>(ent, {std::chrono::high_resolution_clock::now(), std::chrono::high_resolution_clock::now()});

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
            controlSystem->Update(coordinator);
            spawnSystem->Update(coordinator);
            startTime = currentTime;
        }
    }
    return 0;
}