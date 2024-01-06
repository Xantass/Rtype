/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** Main
*/

#include "../inc/Client.hpp"
#include "../../ECS/ECSClient.hpp"
#include "Parallax.hpp"
#include "Menu.hpp"

int main(int ac, char **av)
{
    if (ac != 5)
        return -84;
    // Client client("127.0.0.1", "4242");
    Coordinator coordinator;

    coordinator.Init();
    Graphic::init(1920, 1080, "R-Type");
    Music music = Graphic::loadMusic("assets/Theme.mp3");
    Parallax parallax("assets/parallax/");

    coordinator.RegisterComponent<Position>();
    coordinator.RegisterComponent<Velocity>();
    coordinator.RegisterComponent<Sprite>();
    coordinator.RegisterComponent<Hitbox>();
    coordinator.RegisterComponent<Movable>();

    auto physicSystem = coordinator.RegisterSystem<PhysicSystem>();
    auto graphicSystem = coordinator.RegisterSystem<GraphicalSystem>();
    auto movableSystem = coordinator.RegisterSystem<MovableSystem>();
    auto networkClientSystem = coordinator.RegisterSystem<NetworkClientSystem>();
    auto eventSystem = coordinator.RegisterSystem<EventSystem>();

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
    Menu menu(host, std::to_string(portClient), name);

    // networkClientSystem->Init(host, port, name, portClient);

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
            if (menu.action == "Launch Game") {
                networkClientSystem->Init(menu._host, menu._port, menu._name, portClient);
                menu.action = "Game";
                std::string infos[] = {menu._port, menu._name, menu._nbPlayer};
                coordinator.AddEvent(Event{Event::actions::PARAM, 0, {std::make_any<std::string>(infos[0]), std::make_any<std::string>(infos[1]), std::make_any<std::string>(infos[2])}});
            }
            parallax.draw();
            movableSystem->Update(coordinator);
            eventSystem->RunEvents(coordinator);
            graphicSystem->Update(coordinator);
            if (menu.action == "Game") {
                networkClientSystem->Update(coordinator);
            }
            physicSystem->Update(coordinator);
            startTime = currentTime;
            menu.displayMenu();
            Graphic::endDrawing();
        }
    }
    Graphic::unloadMusic(music);
    Graphic::close();
    return 0;
}
