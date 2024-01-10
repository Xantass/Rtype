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
    coordinator.RegisterComponent<SpawnInfo>();
    coordinator.RegisterComponent<HealthPoint>();
    coordinator.RegisterComponent<Damage>();
    coordinator.RegisterComponent<Path>();

    auto physicSystem = coordinator.RegisterSystem<PhysicSystem>();
    auto controlSystem = coordinator.RegisterSystem<ControlSystem>();
    auto networkServerSystem = coordinator.RegisterSystem<NetworkServerSystem>();
    auto spawnSystem = coordinator.RegisterSystem<SpawnSystem>();
    auto collisionSystem = coordinator.RegisterSystem<CollisionSystem>();
    auto healthSystem = coordinator.RegisterSystem<HealthSystem>();
    auto pathSystem = coordinator.RegisterSystem<PathSystem>();
    
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
    signature3.set(coordinator.GetComponentType<SpawnInfo>());
    signature3.set(coordinator.GetComponentType<Position>());
    coordinator.SetSystemSignature<SpawnClock>(signature3);
    
    Signature signature4;
    signature4.set(coordinator.GetComponentType<Position>());
    signature4.set(coordinator.GetComponentType<Hitbox>());
    signature4.set(coordinator.GetComponentType<HealthPoint>());
    signature4.set(coordinator.GetComponentType<Damage>());
    coordinator.SetSystemSignature<CollisionSystem>(signature4);

    Signature signature5;
    signature5.set(coordinator.GetComponentType<HealthPoint>());
    coordinator.SetSystemSignature<HealthSystem>(signature5);
    
    Signature signature6;
    signature6.set(coordinator.GetComponentType<Position>());
    signature6.set(coordinator.GetComponentType<Velocity>());
    signature6.set(coordinator.GetComponentType<Path>());
    coordinator.SetSystemSignature<PathSystem>(signature6);

    Entity ent = coordinator.CreateEntity();
    coordinator.AddComponent<Position>(ent, {1990, 0});
    coordinator.AddComponent<SpawnClock>(ent, {std::chrono::high_resolution_clock::now(), std::chrono::high_resolution_clock::now(), 2000, 100, 1000});
    coordinator.AddComponent<SpawnInfo>(ent, {-10, 150, 150, 100, 50, 200, 10, 1});

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
            spawnSystem->Update(coordinator);
            pathSystem->Update(coordinator);
            physicSystem->Update(coordinator);
            collisionSystem->Update(coordinator);
            healthSystem->Update(coordinator);
            controlSystem->Update(coordinator);
            startTime = currentTime;
        }
    }
    return 0;
}