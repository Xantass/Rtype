/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** NetworkServerSystem
*/

#include "NetworkServerSystem.hpp"

void NetworkServerSystem::Init()
{
    _socket.non_blocking(true);
    _functions[0] = std::bind(&NetworkServerSystem::response, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    _functions[1] = std::bind(&NetworkServerSystem::connect, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    _functions[2] = nullptr;
    _functions[3] = nullptr;
    _functions[4] = nullptr;
    _functions[5] = nullptr;
    _functions[6] = std::bind(&NetworkServerSystem::pong, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    _functions[7] = nullptr;
    _functions[8] = nullptr;
    _functions[9] = nullptr;
    _functions[10] = std::bind(&NetworkServerSystem::shoot, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    _functions[11] = std::bind(&NetworkServerSystem::move, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    _functions[12] = nullptr;
    _functions[13] = nullptr;
    _startTime = std::chrono::steady_clock::now();
}

int NetworkServerSystem::getClient(int id)
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

std::vector<int> NetworkServerSystem::mergeVectors(const std::vector<int>& vec1, const std::vector<int>& vec2)
{
    std::vector<int> mergedVector = vec1;
    mergedVector.insert(mergedVector.end(), vec2.begin(), vec2.end());
    return mergedVector;
}

std::vector<int> NetworkServerSystem::stringToVector(const std::string& str) {
    std::vector<int> result;
    for (char c : str) {
        result.push_back(static_cast<int>(c));
    }
    return result;
}

std::string NetworkServerSystem::vectorToString(const std::vector<int>& data)
{
    std::stringstream ss;
    for (int num : data) {
        ss << static_cast<char>(num); // Conversion des entiers en caractères
    }
    std::string myString = ss.str();
    return myString;
}

unsigned short NetworkServerSystem::findValidPort(asio::io_context& service)
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

std::vector<unsigned char> NetworkServerSystem::encode(const std::vector<int>& values)
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

std::vector<int> NetworkServerSystem::decode(const std::vector<unsigned char>& encodedData, size_t numBytesToRead)
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

void NetworkServerSystem::response(std::vector<int>& decodedIntegers, udp::endpoint& clientEndpoint, Coordinator &coordinator)
{
    return;
}

void NetworkServerSystem::connect(std::vector<int>& decodedIntegers, udp::endpoint& clientEndpoint, Coordinator &coordinator)
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
    coordinator.AddComponent<Hitbox>(entity, {0, 0, 100, 100, PLAYER});
    coordinator.AddComponent<HealthPoint>(entity, {300, 300});
    coordinator.AddComponent<Damage>(entity, {100, 100});
    sendCreate(entity, coordinator);
    _clients.push_back(Client(username, clientEndpoint, entity));
    // std::cout << _clients.at(_clients.size() - 1).getClientEndpoint() << std::endl;
    std::vector<int> tmp = {_clients.at(_clients.size() - 1).getID()};
    std::vector<unsigned char> buffer = encode(tmp);
    _socket.send_to(asio::buffer(buffer), clientEndpoint);
    sendEcs(coordinator);
}

void NetworkServerSystem::ping(Coordinator &coordinator)
{

    for (auto client : _clients) {
        if (client.getAlive() == false) {
            // std::cout << "DESTROY" << std::endl;
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
        // std::cout << "SEND TO: " << client.getClientEndpoint() << std::endl;
        _socket.send_to(asio::buffer(buffer), client.getClientEndpoint());
    }
}

void NetworkServerSystem::pong(std::vector<int>& decodedIntegers, udp::endpoint& clientEndpoint, Coordinator &coordinator)
{
    int index = getClient(decodedIntegers.at(0));

    // std::cout << "PONG DECODED INTEGERS: " << decodedIntegers.at(0) << std::endl;
    // std::cout << "PONG INDEX: " << index << std::endl;
    if (index == -1) {
        return;
    }
    std::vector<unsigned char> buffer = encode(_PASS);
    _socket.send_to(asio::buffer(buffer), _clients.at(index).getClientEndpoint());
    _clients.at(index).setAlive(true);
}

void NetworkServerSystem::sendDestroy(int entity)
{
    std::vector<int> data = {Cmd::DESTROY, 1, entity};
    std::vector<unsigned char> buffer = encode(data);
    for (auto client : _clients) {
        _socket.send_to(asio::buffer(buffer), client.getClientEndpoint());
    }
}

void NetworkServerSystem::sendCreate(int entity, Coordinator &coordinator)
{
    std::vector<int> res;
    auto& pos = coordinator.GetComponent<Position>(entity);
    auto& vel = coordinator.GetComponent<Velocity>(entity);
    auto& hitbox = coordinator.GetComponent<Hitbox>(entity); 
    res = {Cmd::CREATE, 10, static_cast<int>(entity), static_cast<int>(pos._x * 10), static_cast<int>(pos._y * 10), static_cast<int>(vel._x * 10), static_cast<int>(vel._y * 10), static_cast<int>(hitbox._x), static_cast<int>(hitbox._y), static_cast<int>(hitbox.width), static_cast<int>(hitbox.height), hitbox.type};
    std::vector<unsigned char> data = encode(res);
    for (auto client : _clients) {
        // std::cout << "SEND TO: " << client.getClientEndpoint() << std::endl;
        _socket.send_to(asio::buffer(data), client.getClientEndpoint());
    }
}

int NetworkServerSystem::checkMove(Position& pos, Velocity& vel, Hitbox& hitbox, Entity entity, Coordinator& coordinator)
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

void NetworkServerSystem::move(std::vector<int>& decodedIntegers, udp::endpoint& clientEndpoint, Coordinator &coordinator)
{
    for (auto entity : this->_entities) {
        if (entity == decodedIntegers.at(0)) {
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

void NetworkServerSystem::shoot(std::vector<int>& decodedIntegers, udp::endpoint& clientEndpoint, Coordinator &coordinator)
{
    for (auto entity : this->_entities) {
        if (entity == decodedIntegers.at(0)) {
            Entity bullet = coordinator.CreateEntity();
            auto pos = coordinator.GetComponent<Position>(decodedIntegers.at(0));
            coordinator.AddComponent<Position>(bullet, {pos._x + 100, pos._y + 20});
            coordinator.AddComponent<Velocity>(bullet, {20, 0});
            coordinator.AddComponent<Hitbox>(bullet, {0, 0, 60, 60, BULLET});
            coordinator.AddComponent<Controllable>(bullet, {ENGINE});
            coordinator.AddComponent<HealthPoint>(bullet, {1, 1});
            coordinator.AddComponent<Damage>(bullet, {50, 50});
            std::vector<unsigned char> buffer = encode(_PASS);
            _socket.send_to(asio::buffer(buffer), clientEndpoint);
            this->sendCreate(bullet, coordinator);
            return;
        }
    }
    std::vector<unsigned char> buffer = encode(_UNKNOW);
    _socket.send_to(asio::buffer(buffer), clientEndpoint);
}


void NetworkServerSystem::handleCmd(std::vector<int>& decodedIntegers, udp::endpoint clientEndpoint, Coordinator &coordinator)
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

void NetworkServerSystem::processReceiveData(const std::vector<unsigned char>& data, udp::endpoint clientEndpoint, std::size_t bytesReceived, Coordinator &coordinator)
{
    // std::cout << clientEndpoint << std::endl;
    if (clientEndpoint != asio::ip::udp::endpoint(asio::ip::make_address("0.0.0.0"), 0)) {
        std::vector<int> res = decode(data, bytesReceived);
        handleCmd(res, clientEndpoint, coordinator);
    } else {
        return;
    }
}

void NetworkServerSystem::sendEcs(Coordinator &coordinator)
{
    for (auto client : _clients) {
        std::vector<int> res = {Cmd::POS};
        for (auto entity : this->_entities) {
            auto& pos = coordinator.GetComponent<Position>(entity);
            auto& vel = coordinator.GetComponent<Velocity>(entity);
            auto& hitbox = coordinator.GetComponent<Hitbox>(entity);

            std::vector<int> encode_ = {static_cast<int>(entity), static_cast<int>(pos._x * 10), static_cast<int>(pos._y * 10), static_cast<int>(vel._x * 10), static_cast<int>(vel._y * 10), static_cast<int>(hitbox._x), static_cast<int>(hitbox._y), static_cast<int>(hitbox.width), static_cast<int>(hitbox.height), hitbox.type};
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

void NetworkServerSystem::checkEvent(Coordinator &coordinator)
{
    while (1) {
        auto event = coordinator.GetEvent();
        
        if (event._type == Event::actions::EMPTY) {
            break;
        }
        if (event._type == Event::actions::SPAWN) {
            Entity ennemy = coordinator.CreateEntity();
            coordinator.AddComponent<Position>(ennemy, {1990, (std::any_cast<int>(event._data[0]))});
            coordinator.AddComponent<Velocity>(ennemy, {-20, 0});
            coordinator.AddComponent<Hitbox>(ennemy, {0, 0, 150, 150, ENNEMY});
            coordinator.AddComponent<Controllable>(ennemy, {IA});
            coordinator.AddComponent<HealthPoint>(ennemy, {150, 150});
            coordinator.AddComponent<Damage>(ennemy, {50, 50});
            this->sendCreate(ennemy, coordinator);
            break;
        }
        if (event._type == Event::actions::DESTROY) {
            this->sendDestroy(event._entity);
        }
    }
}

void NetworkServerSystem::Update(Coordinator &coordinator)
{
    std::vector<unsigned char> data(1024);
    udp::endpoint clientEndpoint;
    std::chrono::seconds interval(5);
    std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
    std::chrono::steady_clock::duration elapsedTime = currentTime - _startTime;

    checkEvent(coordinator);
    while (1) {
        try {
            size_t length = _socket.receive_from(asio::buffer(data), clientEndpoint, 0);
            processReceiveData(data, clientEndpoint, length, coordinator);
        } catch (...) {
            break;
        }
    }
    sendEcs(coordinator);
    if (elapsedTime >= interval) {
        ping(coordinator);
        _startTime = currentTime;
    }
}