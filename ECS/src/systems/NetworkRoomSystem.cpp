/*
** EPITECH PROJECT, 2023
** RType [WSL: Fedora]
** File description:
** '
*/

#include "NetworkRoomSystem.hpp"

int NetworkRoomSystem::getClient(int id)
{
    int index = 0;

    // std::cout << "GET CLIENT" << std::endl;
    for (auto client : _clients) {
        // std::cout << "CLIENT ID: " << client.getID() << std::endl;
        if (id == client.getID()) {
            return index;
        }
        index++;
    }
    return -1;
}

std::string NetworkRoomSystem::vectorToString(const std::vector<int>& data)
{
    std::stringstream ss;
    for (int num : data) {
        ss << static_cast<char>(num); // Conversion des entiers en caractères
    }
    std::string myString = ss.str();
    return myString;
}

std::vector<unsigned char> NetworkRoomSystem::encode(const std::vector<int>& values)
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

std::vector<int> NetworkRoomSystem::decode(const std::vector<unsigned char>& encodedData, size_t numBytesToRead)
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

unsigned short NetworkRoomSystem::findValidPort(asio::io_context& service)
{
    asio::ip::udp::socket socket(service);

    for (unsigned short port = 1024; port < 65535; ++port) {
        try {
            asio::ip::udp::endpoint endpoint(asio::ip::udp::v4(), port);
            socket.open(endpoint.protocol());
            socket.bind(endpoint);
            return port;
        } catch (std::exception&) {
        }
    }

    throw std::runtime_error("Could not find an available port.");
}

void NetworkRoomSystem::sendDestroy(int entity)
{
    std::vector<int> data = {Action::DESTROY, 1, entity};
    std::vector<unsigned char> buffer = encode(data);
    for (auto client : _clients) {
        _socket.send_to(asio::buffer(buffer), client.getClientEndpoint());
    }
}

void NetworkRoomSystem::sendCreate(int entity, Coordinator &coordinator)
{
    auto& pos = coordinator.GetComponent<Position>(entity);
    auto& vel = coordinator.GetComponent<Velocity>(entity);
    auto& hitbox = coordinator.GetComponent<Hitbox>(entity);

    std::vector<int> res = {Action::CREATE, 10, static_cast<int>(entity), static_cast<int>(pos._x * 10), static_cast<int>(pos._y * 10), static_cast<int>(vel._x * 10), static_cast<int>(vel._y * 10), static_cast<int>(hitbox._x * 10), static_cast<int>(hitbox._y * 10), static_cast<int>(hitbox.width * 10), static_cast<int>(hitbox.height * 10), hitbox.type};

    std::vector<unsigned char> data = encode(res);
    for (auto client : _clients) {
        std::cout << "SEND TO: " << client.getClientEndpoint() << std::endl;
        _socket.send_to(asio::buffer(data), client.getClientEndpoint());
    }
}

void NetworkRoomSystem::response(std::vector<int>& decodedIntegers, udp::endpoint& clientEndpoint, Coordinator &coordinator)
{
    (void)decodedIntegers;
    (void)clientEndpoint;
    (void)coordinator;
    return;
}

void NetworkRoomSystem::connect(std::vector<int>& decodedIntegers, udp::endpoint& clientEndpoint, Coordinator &coordinator)
{
    std::string username = vectorToString(decodedIntegers);

    // std::cout << "username: " << username << std::endl;

    for (auto client : _clients) {
        if (client.getUsername() == username) {
            std::vector<unsigned char> buffer = encode(_FAIL_CONNECT);
            _socket.send_to(asio::buffer(buffer), clientEndpoint);
            return;
        }
    }
    Entity entity = coordinator.CreateEntity();
    coordinator.AddComponent<Position>(entity, {1, 0});
    coordinator.AddComponent<Velocity>(entity, {0, 0});
    coordinator.AddComponent<Hitbox>(entity, {0, 0, 1, 1, PLAYER});
    sendCreate(entity, coordinator);
    _clients.push_back(Client(username, clientEndpoint, entity));
    // std::cout << _clients.at(_clients.size() - 1).getClientEndpoint() << std::endl;
    std::vector<int> tmp = {_clients.at(_clients.size() - 1).getID()};
    std::vector<unsigned char> buffer = encode(tmp);
    _socket.send_to(asio::buffer(buffer), clientEndpoint);
    sendEcs(coordinator);
}

void NetworkRoomSystem::ping(Coordinator &coordinator)
{

    for (auto client : _clients) {
        if (client.getAlive() == false) {
            std::cout << "DESTROY" << std::endl;
            coordinator.DestroyEntity(client.getID());
            sendDestroy(client.getID());
        }
    }
    _clients.erase(
        std::remove_if(
            _clients.begin(),
            _clients.end(),
            [](Client& client) {
                if (!client.getAlive()) {
                    return true;
                } else {
                    client.setAlive(false);
                    return false;
                }
            }
        ),
    _clients.end()
    );
    for (auto client : _clients) {
        std::vector<unsigned char> buffer = encode(_PING);
        std::cout << "SEND TO: " << client.getClientEndpoint() << std::endl;
        _socket.send_to(asio::buffer(buffer), client.getClientEndpoint());
    }
}

void NetworkRoomSystem::pong(std::vector<int>& decodedIntegers, udp::endpoint& clientEndpoint, Coordinator &coordinator)
{
    (void)clientEndpoint;
    (void)coordinator;
    int index = getClient(decodedIntegers.at(0));

    std::cout << "PONG DECODED INTEGERS: " << decodedIntegers.at(0) << std::endl;
    std::cout << "PONG INDEX: " << index << std::endl;
    if (index == -1) {
        return;
    }
    std::vector<unsigned char> buffer = encode(_PASS);
    _socket.send_to(asio::buffer(buffer), _clients.at(index).getClientEndpoint());
    _clients.at(index).setAlive(true);
}

int NetworkRoomSystem::checkMove(Position& pos, Velocity& vel, Hitbox& hitbox, Entity entity, Coordinator& coordinator)
{
    for (auto entity2 : this->_entities) {
        if (entity == entity2)
            continue;
        auto& pos2 = coordinator.GetComponent<Position>(entity2);
        auto& hitbox2 = coordinator.GetComponent<Hitbox>(entity2);

        if ((pos._x + vel._x) + hitbox._x + hitbox.width >= pos2._x + hitbox2._x &&
            (pos._x + vel._x) + hitbox._x <= pos2._x + hitbox2._x + hitbox2.width &&
            (pos._y + vel._y) + hitbox._y + hitbox.height >= pos2._y + hitbox2._y &&
            (pos._y + vel._y) + hitbox._y <= pos2._y + hitbox2._y + hitbox2.height &&
            hitbox.type == PLAYER && hitbox2.type == PLAYER) {
            return -1;
        }
        if ((pos._x + vel._x) + hitbox._x + hitbox.width >= pos2._x + hitbox2._x &&
            (pos._x + vel._x) + hitbox._x <= pos2._x + hitbox2._x + hitbox2.width &&
            (pos._y + vel._y) + hitbox._y + hitbox.height >= pos2._y + hitbox2._y &&
            (pos._y + vel._y) + hitbox._y <= pos2._y + hitbox2._y + hitbox2.height &&
            hitbox.type == PLAYER && hitbox2.type == ENNEMY) {
            return -1;
        }
    }
    return 0;
}

void NetworkRoomSystem::move(std::vector<int>& decodedIntegers, udp::endpoint& clientEndpoint, Coordinator &coordinator)
{
    // std::cout << "MOVE CLIENT" << std::endl;
    for (auto entity : this->_entities) {
        if (static_cast<int>(entity) == decodedIntegers.at(0)) {
            auto& vel = coordinator.GetComponent<Velocity>(entity);
            auto& pos = coordinator.GetComponent<Position>(entity);
            auto& hitbox = coordinator.GetComponent<Hitbox>(entity);

            if (checkMove(pos, vel, hitbox, entity, coordinator) == -1) {
                std::vector<unsigned char> buffer = encode(_UNKNOW);
                _socket.send_to(asio::buffer(buffer), clientEndpoint);
                return;
            }

            vel._x = decodedIntegers.at(1);
            vel._y = decodedIntegers.at(2);
            std::vector<unsigned char> buffer = encode(_PASS);
            _socket.send_to(asio::buffer(buffer), clientEndpoint);
            return;
        }
    }
    std::vector<unsigned char> buffer = encode(_UNKNOW);
    _socket.send_to(asio::buffer(buffer), clientEndpoint);
}

void NetworkRoomSystem::handleCmd(std::vector<int>& decodedIntegers, udp::endpoint clientEndpoint, Coordinator &coordinator)
{
    int index = decodedIntegers.at(0);

    // std::cout << "INDEX: " << index << std::endl;
    if (index < 0 || index > 12)
        return;
    if (_functions[index] != nullptr) {
        decodedIntegers.erase(decodedIntegers.begin(), decodedIntegers.begin() + 2);
        _functions[index](decodedIntegers, clientEndpoint, coordinator);
    }
    else {
        std::vector<unsigned char> buffer = encode(_UNKNOW);
        _socket.send_to(asio::buffer(buffer), clientEndpoint);
    }
}

void NetworkRoomSystem::processReceiveData(const std::vector<unsigned char>& data, udp::endpoint clientEndpoint, std::size_t bytesReceived, Coordinator &coordinator)
{
    std::cout << clientEndpoint << std::endl;
    if (clientEndpoint != asio::ip::udp::endpoint(asio::ip::make_address("0.0.0.0"), 0)) {
        std::vector<int> res = decode(data, bytesReceived);
        handleCmd(res, clientEndpoint, coordinator);
    } else {
        return;
    }
}

void NetworkRoomSystem::sendEcs(Coordinator &coordinator)
{
    for (auto client : _clients) {
        std::vector<int> res = {Cmd::POS};
        for (auto entity : this->_entities) {
            auto& pos = coordinator.GetComponent<Position>(entity);
            auto& vel = coordinator.GetComponent<Velocity>(entity);
            auto& hitbox = coordinator.GetComponent<Hitbox>(entity);

            std::vector<int> encode_ = {static_cast<int>(entity), static_cast<int>(pos._x * 10), static_cast<int>(pos._y * 10), static_cast<int>(vel._x * 10), static_cast<int>(vel._y * 10), static_cast<int>(hitbox._x * 10), static_cast<int>(hitbox._y * 10), static_cast<int>(hitbox.width * 10), static_cast<int>(hitbox.height * 10), hitbox.type};
            for (auto i : encode_)
                res.push_back(i);
        }
        // std::cout << "SEND ECS" << std::endl;
        // for (auto i : res)
        //     std::cout << i << std::endl;
        std::vector<unsigned char> data = encode(res);
        _socket.send_to(asio::buffer(data), client.getClientEndpoint());
    }
}

void NetworkRoomSystem::Init(int port)
{
    udp::endpoint endpoint(udp::v4(), port);
    _socket.close();
    _socket.open(endpoint.protocol());
    _socket.bind(endpoint);
    _socket.non_blocking(true);
    _functions[0] = std::bind(&NetworkRoomSystem::response, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    _functions[1] = std::bind(&NetworkRoomSystem::connect, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    _functions[2] = nullptr;
    _functions[3] = nullptr;
    _functions[4] = nullptr;
    _functions[5] = nullptr;
    _functions[6] = std::bind(&NetworkRoomSystem::pong, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    _functions[7] = nullptr;
    _functions[8] = nullptr;
    _functions[9] = nullptr;
    _functions[10] = nullptr;
    _functions[11] = std::bind(&NetworkRoomSystem::move, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    _functions[12] = nullptr;
    _functions[13] = nullptr;
    return;
}

void NetworkRoomSystem::Update(Coordinator& coordinator)
{
    (void)coordinator;
    return;
}
