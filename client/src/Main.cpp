/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** Main
*/

#include <fstream>
#include "../inc/Client.hpp"
#include "../../ECS/ECSClient.hpp"
#include "Parallax.hpp"
#include "Menu.hpp"
#include "Chat.hpp"

std::string fileToBase64(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file) {
        std::cerr << "Erreur lors de l'ouverture du fichier." << std::endl;
        return "";
    }

    std::ostringstream base64Stream;
    base64Stream << file.rdbuf();

    return base64Stream.str();
}

int main(int ac, char **av)
{
    if (ac != 5)
        return -84;
    std::ofstream fichier;
    fichier.open("room.txt", std::ofstream::out | std::ofstream::trunc);

    if (fichier.is_open()) {
        fichier << "PORT\tNAME\tNB_PLAYER" << std::endl;
        fichier.close();
    } else {
        std::cerr << "Impossible d'ouvrir le fichier." << std::endl;
    }

    Coordinator coordinator;
    AssetManager assetManager;

    coordinator.Init();
    Graphic::init(1920, 1080, "R-Type");
    Graphic::toggleFullScreen();
    Parallax parallax("assets/parallax/");
    Chat chat(av[3]);

    coordinator.RegisterComponent<Position>();
    coordinator.RegisterComponent<Velocity>();
    coordinator.RegisterComponent<Sprite>();
    coordinator.RegisterComponent<Hitbox>();
    coordinator.RegisterComponent<Movable>();
    coordinator.RegisterComponent<HealthPoint>();

    auto physicSystem = coordinator.RegisterSystem<PhysicSystem>();
    auto graphicSystem = coordinator.RegisterSystem<GraphicalSystem>();
    auto movableSystem = coordinator.RegisterSystem<MovableSystem>();
    auto networkClientSystem = coordinator.RegisterSystem<NetworkClientSystem>();
    auto eventSystem = coordinator.RegisterSystem<EventSystem>();
    auto logger = coordinator.RegisterSystem<Logger>();

    Signature signature2;

    signature2.set(coordinator.GetComponentType<Position>());
    signature2.set(coordinator.GetComponentType<Velocity>());
    signature2.set(coordinator.GetComponentType<Sprite>());
    coordinator.SetSystemSignature<GraphicalSystem>(signature2);

    Signature signature3;

    signature3.set(coordinator.GetComponentType<Position>());
    signature3.set(coordinator.GetComponentType<Velocity>());
    signature3.set(coordinator.GetComponentType<Hitbox>());
    signature3.set(coordinator.GetComponentType<HealthPoint>());
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
    Menu menu(host, std::to_string(portClient), name, coordinator);

    networkClientSystem->Init(host, port, name, portClient);

    std::chrono::milliseconds interval(16);
    std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();
    std::chrono::steady_clock::duration elapsedTime;
    while (!Graphic::shouldCloseWindow()) {
        currentTime = std::chrono::steady_clock::now();
        elapsedTime = currentTime - startTime;
        if (elapsedTime >= interval) {
            Graphic::beginDrawing();
            Graphic::clearBackground(RBLACK);
            if (menu.action == "Launch Game") {
                if (menu._selectEnnemyTwo == -1 || menu._selectEnnemyElite == -1 || menu._selectEnnemyBoss == -1 || menu._selectEnnemyBullet == -1) {
                    menu.action = "Create Room";
                } else {
                    menu.action = "";
                    std::string infos[] = {menu._port, menu._name, menu._nbPlayer};
                    coordinator.AddEvent(Event{Event::actions::PARAM, 0, {std::make_any<int>(menu._selectBullet), std::make_any<int>(menu._selectEnnemy), std::make_any<int>(menu._selectEnnemyTwo), std::make_any<int>(menu._selectEnnemyElite), std::make_any<int>(menu._selectEnnemyBoss), std::make_any<int>(menu._selectEnnemyBullet), std::make_any<std::string>(infos[0]), std::make_any<std::string>(infos[1]), std::make_any<std::string>(infos[2])}});
                    menu._selectBullet = -1;
                    menu._selectEnnemy = -1;
                    menu._selectEnnemyTwo = -1;
                    menu._selectEnnemyElite = -1;
                    menu._selectEnnemyBoss = -1;
                    menu._selectEnnemyBullet = -1;
                }
            }
            if (menu.action == "Send Sprite") {
                std::string base64 = fileToBase64(menu._pathSprite);
                if (base64 == "") {
                    menu._errorLoad = "Error: can't open file";
                    menu.action = "Load Sprite";
                } else {
                    menu.action = "";
                    menu._errorLoad = "";
                    std::string fileName = std::filesystem::path(menu._pathSprite).filename().string();
                    coordinator.AddEvent(Event{Event::actions::SEND_SPRITE, 0, {std::make_any<std::string>(base64), std::make_any<std::string>(fileName)}});
                }

            }
            parallax.draw();
            if (!chat.isOpen())
                movableSystem->Update(coordinator);
            eventSystem->RunEvents(coordinator, assetManager);
            graphicSystem->Update(coordinator);
            networkClientSystem->Update(coordinator);
            eventSystem->RunEvents(coordinator, assetManager);
            physicSystem->Update(coordinator);
            if (menu.action == "Game") {
                chat.displayChatWindow(coordinator);
                logger->Update(coordinator);
            }
            startTime = currentTime;
            menu.displayMenu(assetManager);
            Graphic::endDrawing();
        }
    }
    Graphic::close();
    return 0;
}
