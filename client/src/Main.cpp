/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** Main
*/

#include "Client.cpp"
#include "Coordinator.hpp"
#include "components/Position.hpp"
#include "components/Velocity.hpp"
#include "components/Sprite.hpp"
#include "components/Hitbox.hpp"
#include "systems/PhysicSystem.hpp"
#include "systems/GraphicalSystem.hpp"
#include "systems/ParallaxSystem.hpp"
#include "systems/MovableSystem.hpp"
#include "systems/NetworkClientSystem.hpp"
#include "Signature.hpp"
#include "Graphic.hpp"

int main(int ac, char **av)
{
    if (ac != 5)
        return -84;
    Client client("127.0.0.1", "4242");
    Coordinator coordinator;

    coordinator.Init();
    Graphic::init(1920, 1080, "R-Type");
    Music music = Graphic::loadMusic("assets/Theme.mp3");

    coordinator.RegisterComponent<Position>();
    coordinator.RegisterComponent<Velocity>();
    coordinator.RegisterComponent<Sprite>();
    coordinator.RegisterComponent<Hitbox>();
    coordinator.RegisterComponent<Movable>();

    auto physicSystem = coordinator.RegisterSystem<PhysicSystem>();
    auto graphicSystem = coordinator.RegisterSystem<GraphicalSystem>();
    auto parallaxSystem = coordinator.RegisterSystem<ParallaxSystem>();
    auto movableSystem = coordinator.RegisterSystem<MovableSystem>();
    auto networkClientSystem = coordinator.RegisterSystem<NetworkClientSystem>();

    Signature signature;

    signature.set(coordinator.GetComponentType<Position>());
    signature.set(coordinator.GetComponentType<Sprite>());
    coordinator.SetSystemSignature<ParallaxSystem>(signature);

    Signature signature2;

    signature2.set(coordinator.GetComponentType<Position>());
    signature2.set(coordinator.GetComponentType<Velocity>());
    signature2.set(coordinator.GetComponentType<Sprite>());
    coordinator.SetSystemSignature<GraphicalSystem>(signature2);

    Signature signature3;

    signature3.set(coordinator.GetComponentType<Position>());
    signature3.set(coordinator.GetComponentType<Velocity>());
    signature3.set(coordinator.GetComponentType<Hitbox>());
    coordinator.SetSystemSignature<PhysicSystem>(signature3);
    coordinator.SetSystemSignature<NetworkClientSystem>(signature3);

    Signature signature4;

    signature4.set(coordinator.GetComponentType<Movable>());
    signature4.set(coordinator.GetComponentType<Velocity>());
    coordinator.SetSystemSignature<MovableSystem>(signature4);

    std::string host = av[1];
    std::string port = av[2];
    std::string name = av[3];
    int portClient = atoi(av[4]);

    networkClientSystem->Init(coordinator, host, port, name, portClient);

    Entity entity2 = coordinator.CreateEntity();
    coordinator.AddComponent<Position>(entity2, {1920, 0});
    coordinator.AddComponent<Velocity>(entity2, {-2, 0});
    coordinator.AddComponent<Hitbox>(entity2, {0, 0, 0, 0, OTHER});
    coordinator.AddComponent<Sprite>(entity2, {Graphic::loadTexture("assets/parallax-space-big-planet.png")});

    Entity entity3 = coordinator.CreateEntity();
    coordinator.AddComponent<Position>(entity3, {1920, 0});
    coordinator.AddComponent<Velocity>(entity3, {-2.3, 0});
    coordinator.AddComponent<Hitbox>(entity3, {0, 0, 0, 0, OTHER});
    coordinator.AddComponent<Sprite>(entity3, {Graphic::loadTexture("assets/parallax-space-far-planets.png")});

    Entity entity4 = coordinator.CreateEntity();
    coordinator.AddComponent<Position>(entity4, {1920, 0});
    coordinator.AddComponent<Velocity>(entity4, {-2.6, 0});
    coordinator.AddComponent<Hitbox>(entity4, {0, 0, 0, 0, OTHER});
    coordinator.AddComponent<Sprite>(entity4, {Graphic::loadTexture("assets/parallax-space-ring-planet.png")});

    Entity entity5 = coordinator.CreateEntity();
    coordinator.AddComponent<Position>(entity5, {1920, 0});
    coordinator.AddComponent<Velocity>(entity5, {-2.9, 0});
    coordinator.AddComponent<Hitbox>(entity5, {0, 0, 0, 0, OTHER});
    coordinator.AddComponent<Sprite>(entity5, {Graphic::loadTexture("assets/parallax-space-stars.png")});

    std::cout << "Entity 2: " << entity2 << std::endl;
    std::cout << "Entity 3: " << entity3 << std::endl;
    std::cout << "Entity 4: " << entity4 << std::endl;
    std::cout << "Entity 5: " << entity5 << std::endl;

    Graphic::playMusic(music);
    std::chrono::milliseconds interval(10);
    std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();
    std::chrono::steady_clock::duration elapsedTime;
    while (!Graphic::shouldCloseWindow()) {
        currentTime = std::chrono::steady_clock::now();
        elapsedTime = currentTime - startTime;
        if (elapsedTime >= interval) {
            Graphic::updateMusic(music);
            Graphic::beginDrawing();
            Graphic::clearBackground(RBLACK); 
            movableSystem->Update(coordinator);
            parallaxSystem->Update(coordinator);
            graphicSystem->Update(coordinator);
            networkClientSystem->Update(coordinator);
            physicSystem->Update(coordinator);
            startTime = currentTime;
            Graphic::endDrawing();
        }
    }
    Graphic::unloadMusic(music);
    Graphic::close();
    return 0;
}
