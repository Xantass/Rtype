/*
** EPITECH PROJECT, 2023
** RType [WSL: Fedora]
** File description:
** room
*/

#include "room.hpp"

int room(int nbPlayer, int port, udp::endpoint clientEndpoint, std::string nameAdmin, std::map<int, std::tuple<std::string, std::string>> sprite, std::vector<int> selectSprites)
{
    (void)nbPlayer;
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

    auto physicSystem = coordinator.RegisterSystem<PhysicSystem>();
    auto controlSystem = coordinator.RegisterSystem<ControlSystem>();
    auto networkRoomSystem = coordinator.RegisterSystem<NetworkRoomSystem>();
    auto spawnSystem = coordinator.RegisterSystem<SpawnSystem>();
    auto collisionSystem = coordinator.RegisterSystem<CollisionSystem>();
    auto healthSystem = coordinator.RegisterSystem<HealthSystem>();
    
    Signature signature;

    signature.set(coordinator.GetComponentType<Position>());
    signature.set(coordinator.GetComponentType<Velocity>());
    signature.set(coordinator.GetComponentType<Hitbox>());
    coordinator.SetSystemSignature<PhysicSystem>(signature);
    coordinator.SetSystemSignature<NetworkRoomSystem>(signature);
    
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

    Entity cl1 = coordinator.CreateEntity();
    coordinator.AddComponent<Position>(cl1, {1990, 0});
    coordinator.AddComponent<SpawnClock>(cl1, {std::chrono::high_resolution_clock::now(), std::chrono::high_resolution_clock::now(), 0});
    coordinator.AddComponent<SpawnInfo>(cl1, {3, 100, 900, -5, 30, 20, 100, 110, 1, 1, 1});
    Entity cl2 = coordinator.CreateEntity();
    coordinator.AddComponent<Position>(cl2, {1990, 0});
    coordinator.AddComponent<SpawnClock>(cl2, {std::chrono::high_resolution_clock::now(), std::chrono::high_resolution_clock::now(), 0});
    coordinator.AddComponent<SpawnInfo>(cl2, {2, 300, 700, -10, 30, 20, 100, 110, 1, 1, 1});
    Entity cl3 = coordinator.CreateEntity();
    coordinator.AddComponent<Position>(cl3, {1990, 0});
    coordinator.AddComponent<SpawnClock>(cl3, {std::chrono::high_resolution_clock::now(), std::chrono::high_resolution_clock::now(), 0});
    coordinator.AddComponent<SpawnInfo>(cl3, {5, 200, 900, -15, 30, 20, 100, 110, 1, 1, 1});

    networkRoomSystem->Init(port, clientEndpoint, nameAdmin, nbPlayer, sprite, selectSprites);
    std::chrono::milliseconds interval(16);
    std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();
    std::chrono::steady_clock::duration elapsedTime;
    while (1) {
        currentTime = std::chrono::steady_clock::now();
        elapsedTime = currentTime - startTime;
        if (elapsedTime >= interval) {
            networkRoomSystem->Update(coordinator);
            physicSystem->Update(coordinator);
            controlSystem->Update(coordinator);
            spawnSystem->Update(coordinator);
            collisionSystem->Update(coordinator);
            healthSystem->Update(coordinator);
            startTime = currentTime;
        }
    }
    return 0;
}