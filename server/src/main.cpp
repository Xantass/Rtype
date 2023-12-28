/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** main
*/


#include "main.hpp"

int main(int argc, char **argv)
{
    if (argc != 1)
        return 84;
    (void)argv;

    Coordinator coordinator;

    coordinator.Init();

    auto networkServerSystem = coordinator.RegisterSystem<NetworkServerSystem>();

    Signature signature;

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
            startTime = currentTime;
        }
    }
    return 0;
}