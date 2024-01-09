/*
** EPITECH PROJECT, 2023
** RType [WSL: Fedora]
** File description:
** room
*/

#include "room.hpp"

int room(int nbPlayer, int port)
{
    (void)nbPlayer;
    Coordinator coordinator;

    coordinator.Init();

    coordinator.RegisterComponent<Position>();
    coordinator.RegisterComponent<Velocity>();
    coordinator.RegisterComponent<Hitbox>();

    auto physicSystem = coordinator.RegisterSystem<PhysicSystem>();
    auto networkRoomSystem = coordinator.RegisterSystem<NetworkRoomSystem>();

    Signature signature;

    signature.set(coordinator.GetComponentType<Position>());
    signature.set(coordinator.GetComponentType<Velocity>());
    signature.set(coordinator.GetComponentType<Hitbox>());
    coordinator.SetSystemSignature<PhysicSystem>(signature);
    coordinator.SetSystemSignature<NetworkRoomSystem>(signature);

    networkRoomSystem->Init(port);
    std::chrono::milliseconds interval(10);
    std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();
    std::chrono::steady_clock::duration elapsedTime;
    while (1) {
        currentTime = std::chrono::steady_clock::now();
        elapsedTime = currentTime - startTime;
        if (elapsedTime >= interval) {
            networkRoomSystem->Update(coordinator);
            physicSystem->Update(coordinator);
            startTime = currentTime;
        }
    }
    return 0;
}