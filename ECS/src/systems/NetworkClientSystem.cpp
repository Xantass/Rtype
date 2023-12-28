/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** NetworkClientSystem
*/

#include "NetworkClientSystem.hpp"
#include "components/Sprite.hpp"
#include "../components/Movable.hpp"
#include "Graphic.hpp"

using asio::ip::udp;

#define CHECK_ZERO(x) x == 0 ? static_cast<float>(x) : static_cast<float>(x) / 10
#define CHECK_ACTION(x) x == Event::MOVE ? 11 : 10

void NetworkClientSystem::Init(std::string host, std::string port, std::string name, int portClient)
{
    udp::endpoint endpoint(udp::v4(), portClient);
    _socket.close();
    _socket.open(endpoint.protocol());
    _socket.bind(endpoint);
    _serverEndpoint = udp::endpoint(asio::ip::make_address(host), atoi(port.c_str()));
    std::vector<int> tmp = mergeVectors(_CONNECT, stringToVector(name));
    std::vector<unsigned char> buffer = encode(tmp);
    _socket.send_to(asio::buffer(buffer), _serverEndpoint);
    std::vector<unsigned char> data(1024);
    std::cout << "CREATE ENTITY AFTER RECEIVE FROM" << std::endl;
    size_t length = _socket.receive_from(asio::buffer(data), _serverEndpoint, 0);
    std::vector<int> decodedIntegers = decode(data, length);
    _id = decodedIntegers.at(0);
    _functions[0] = nullptr;
    _functions[1] = nullptr;
    _functions[2] = nullptr;
    _functions[3] = nullptr;
    _functions[4] = std::bind(&NetworkClientSystem::pos, this, std::placeholders::_1, std::placeholders::_2);
    _functions[5] = std::bind(&NetworkClientSystem::ping, this, std::placeholders::_1, std::placeholders::_2);
    _functions[6] = nullptr;
    _functions[7] = nullptr;
    _functions[8] = nullptr;
    _functions[9] = nullptr;
    _functions[10] = nullptr;
    _functions[11] = nullptr;
    _functions[12] = std::bind(&NetworkClientSystem::destroyEntity, this, std::placeholders::_1, std::placeholders::_2);
    _functions[13] = std::bind(&NetworkClientSystem::createEntity, this, std::placeholders::_1, std::placeholders::_2);
    _socket.non_blocking(true);
}

HitboxType NetworkClientSystem::deterType(int x)
{
    if (x == 1)
        return PLAYER;
    if (x == 0)
        return ENNEMY;
    return OTHER;
}

void NetworkClientSystem::createEntities(std::vector<int> decodedInteger, Coordinator &coordinator)
{
    // std::cout << "CREATE" << std::endl;
    decodedInteger.erase(decodedInteger.begin(), decodedInteger.begin() + 1);
    // std::cout << "SIZE: " << decodedInteger.size() << std::endl;
    while (decodedInteger.empty() == false) {
        //ADD INT FOR ID ENTITY
        Entity entity = coordinator.CreateEntity(decodedInteger.at(0));
        if (static_cast<int>(entity) == _id) {
            coordinator.AddComponent<Movable>(entity, {NONE});
        }
        if (deterType(decodedInteger.at(9)) == PLAYER) {
            coordinator.AddComponent<Sprite>(entity, {Graphic::loadTexture("assets/spaceship.png")});
        }
        coordinator.AddComponent<Position>(entity, {CHECK_ZERO(decodedInteger.at(1)), CHECK_ZERO(decodedInteger.at(2))});
        coordinator.AddComponent<Velocity>(entity, {CHECK_ZERO(decodedInteger.at(3)), CHECK_ZERO(decodedInteger.at(4))});
        coordinator.AddComponent<Hitbox>(entity, {CHECK_ZERO(decodedInteger.at(5)), CHECK_ZERO(decodedInteger.at(6)), CHECK_ZERO(decodedInteger.at(7)), CHECK_ZERO(decodedInteger.at(8)), deterType(decodedInteger.at(9))});
        decodedInteger.erase(decodedInteger.begin(), decodedInteger.begin() + 10);
    }
}

unsigned short NetworkClientSystem::findValidPort(asio::io_context& service)
{
    udp::socket socket(service);

    // Commencer à partir d'un certain port (par exemple 5000)
    unsigned short startingPort = 5000;
    unsigned short maxPort = 65535; // Port maximum possible

    for (unsigned short port = startingPort; port <= maxPort; ++port) {
        try {
            udp::endpoint endpoint(udp::v4(), port);
            socket.open(endpoint.protocol());
            socket.bind(endpoint);
            return port;
        } catch (std::exception&) {
            // Le port est déjà utilisé, essayez le suivant
        }
    }

    throw std::runtime_error("Tous les ports sont utilisés");
}

std::vector<int> NetworkClientSystem::mergeVectors(const std::vector<int>& vec1, const std::vector<int>& vec2)
{
    std::vector<int> mergedVector = vec1;
    mergedVector.insert(mergedVector.end(), vec2.begin(), vec2.end());
    return mergedVector;
}

std::vector<int> NetworkClientSystem::stringToVector(const std::string& str) {
    std::vector<int> result;
    for (char c : str) {
        result.push_back(static_cast<int>(c));
    }
    return result;
}

void NetworkClientSystem::ping(std::vector<int>& decodedIntegers, Coordinator &coordinator)
{
    (void)coordinator;
    decodedIntegers.erase(decodedIntegers.begin(), decodedIntegers.begin() + 2);
    std::vector<int> tmp = {_id};
    std::cout << "SEND PONG WITH ID: "<< _id << std::endl;
    std::vector<unsigned char> buffer = encode(mergeVectors(_PONG, tmp));
    _socket.send_to(asio::buffer(buffer), _serverEndpoint);
}

void NetworkClientSystem::pos(std::vector<int>& decodedIntegers, Coordinator &coordinator)
{
    // std::cout << "POS" << std::endl;
    // std::cout << "SIZE: " << decodedIntegers.size() << std::endl;
    decodedIntegers.erase(decodedIntegers.begin(), decodedIntegers.begin() + 1);
    while (decodedIntegers.empty() == false) {
        for (auto entity : this->_entities) {
            if (static_cast<int>(entity) == decodedIntegers.at(0)) {
                auto& pos = coordinator.GetComponent<Position>(entity);
                auto& vel = coordinator.GetComponent<Velocity>(entity);
                auto& hitbox = coordinator.GetComponent<Hitbox>(entity);

                pos._x = CHECK_ZERO(decodedIntegers.at(1));
                pos._y = CHECK_ZERO(decodedIntegers.at(2));
                vel._x = CHECK_ZERO(decodedIntegers.at(3));
                vel._y = CHECK_ZERO(decodedIntegers.at(4));
                hitbox._x = CHECK_ZERO(decodedIntegers.at(5));
                hitbox._y = CHECK_ZERO(decodedIntegers.at(6));
                hitbox.width = CHECK_ZERO(decodedIntegers.at(7));
                hitbox.height = CHECK_ZERO(decodedIntegers.at(8));
                hitbox.type = deterType(decodedIntegers.at(9));
                break;
            }
        }
        decodedIntegers.erase(decodedIntegers.begin(), decodedIntegers.begin() + 10);
    }
    std::vector<unsigned char> buffer = encode(mergeVectors(_OK, {_id}));
    _socket.send_to(asio::buffer(buffer), _serverEndpoint);
}

void NetworkClientSystem::createEntity(std::vector<int> decodedIntegers, Coordinator &coordinator)
{
    std::cout << "CREATE" << std::endl;
    decodedIntegers.erase(decodedIntegers.begin(), decodedIntegers.begin() + 2);
    while (decodedIntegers.empty() == false) {
        Entity entity = coordinator.CreateEntity(decodedIntegers.at(0));
        if (static_cast<int>(entity) == _id) {
            coordinator.AddComponent<Movable>(entity, {NONE});
        }
        if (deterType(decodedIntegers.at(9)) == PLAYER) {
            coordinator.AddComponent<Sprite>(entity, {Graphic::loadTexture("assets/spaceship.png")});
        }
        coordinator.AddComponent<Position>(entity, {CHECK_ZERO(decodedIntegers.at(1)), CHECK_ZERO(decodedIntegers.at(2))});
        coordinator.AddComponent<Velocity>(entity, {CHECK_ZERO(decodedIntegers.at(3)), CHECK_ZERO(decodedIntegers.at(4))});
        coordinator.AddComponent<Hitbox>(entity, {CHECK_ZERO(decodedIntegers.at(5)), CHECK_ZERO(decodedIntegers.at(6)), CHECK_ZERO(decodedIntegers.at(7)), CHECK_ZERO(decodedIntegers.at(8)), deterType(decodedIntegers.at(9))});
        decodedIntegers.erase(decodedIntegers.begin(), decodedIntegers.begin() + 10);
    }
}

void NetworkClientSystem::destroyEntity(std::vector<int> decodedIntegers, Coordinator &coordinator)
{
    decodedIntegers.erase(decodedIntegers.begin(), decodedIntegers.begin() + 2);
    coordinator.DestroyEntity(decodedIntegers.at(0));
}

void NetworkClientSystem::handleCmd(std::vector<int>& decodedIntegers, Coordinator &coordinator)
{
    int index = decodedIntegers.at(0);

    // std::cout << "RECEIVE CMD: " << std::endl;
    // for (auto i : decodedIntegers)
    //     std::cout << i << std::endl;
    if (_functions[index] != nullptr) {
        _functions[index](decodedIntegers, coordinator);
    }
    else {
        std::vector<unsigned char> buffer = encode(_UNKNOW);
        _socket.send_to(asio::buffer(buffer), _serverEndpoint);
    }
}

std::vector<unsigned char> NetworkClientSystem::encode(const std::vector<int>& values)
{
    std::vector<unsigned char> encodedData;
    for (int value : values) {
        unsigned int intValue = (value >= 0) ? (static_cast<unsigned int>(value) << 1) : ((-value) << 1 | 1);

        while (intValue >= 128) {
            encodedData.push_back((intValue & 0x7F) | 0x80);
            intValue >>= 7;
        }
        encodedData.push_back(intValue & 0x7F);
    }
    return encodedData;
}

std::vector<int> NetworkClientSystem::decode(const std::vector<unsigned char>& encodedData, size_t numBytesToRead)
{
    std::vector<int> decodedValues;
    int value = 0;
    int shift = 0;
    size_t bytesRead = 0;
    size_t totalShifts = 0;

    for (unsigned char byte : encodedData) {
        value |= (byte & 0x7F) << shift;
        totalShifts += 7;
        shift += 7;

        if (!(byte & 0x80)) {
            if (value & 1) {
                value = -(value >> 1);
            } else {
                value >>= 1;
            }
            decodedValues.push_back(value);
            value = 0;
            shift = 0;
            bytesRead++;

            if (bytesRead >= numBytesToRead || totalShifts >= numBytesToRead * 7)
                break;
        }
    }
    return decodedValues;
}

void NetworkClientSystem::paramEvent(Event& event)
{
    (void)event;
    return;
}

void NetworkClientSystem::joinEvent(Event& event, Coordinator& coordinator)
{
    std::vector<std::string> list = std::any_cast<std::vector<std::string>>(event._data);
    _serverEndpoint = udp::endpoint(asio::ip::make_address(list.at(0)), atoi(list.at(1).c_str()));
    std::vector<int> tmp = mergeVectors(_CONNECT, stringToVector(list.at(2)));
    std::vector<unsigned char> buffer = encode(tmp);
    _socket.send_to(asio::buffer(buffer), _serverEndpoint);
    std::vector<unsigned char> data(1024);
    std::cout << "CREATE ENTITY AFTER RECEIVE FROM" << std::endl;
    size_t length = _socket.receive_from(asio::buffer(data), _serverEndpoint, 0);
    std::vector<int> decodedIntegers = decode(data, length);
    _id = decodedIntegers.at(0);
    // std::cout << "id: " << _id << std::endl;
    length = _socket.receive_from(asio::buffer(data), _serverEndpoint, 0);
    decodedIntegers = decode(data, length);
    for (auto i : decodedIntegers)
        std::cout << i << std::endl;
    createEntities(decodedIntegers, coordinator);
    return;
}

void NetworkClientSystem::checkEvent(Coordinator &coordinator)
{
    while (1) {
        auto event = coordinator.GetEvent();
        
        if (event._type == Event::EMPTY) {
            break;
        }
        if (event._type == Event::MOVE) {
            std::vector<int> tmp = mergeVectors({CHECK_ACTION(event._type), 3}, {static_cast<int>(event._entity), static_cast<int>(std::any_cast<Velocity>(event._data)._x * 10), static_cast<int>(std::any_cast<Velocity>(event._data)._y * 10)});
            std::vector<unsigned char> buffer = encode(tmp);
            _socket.send_to(asio::buffer(buffer), _serverEndpoint);
        }
        if (event._type == Event::PARAM) {
            paramEvent(event);
        }
        if (event._type == Event::JOIN) {
            joinEvent(event, coordinator);
        }
    }
}

void NetworkClientSystem::Update(Coordinator &coordinator)
{
    std::vector<unsigned char> data(1024);
    udp::endpoint receiveEndpoint;

    checkEvent(coordinator);
    while (1) {
        try {
            size_t length = _socket.receive_from(asio::buffer(data), receiveEndpoint, 0);
            std::vector<int> decodedIntegers = decode(data, length);
            handleCmd(decodedIntegers, coordinator);
        } catch (const std::system_error& e) {
            break;
        }
    }
}