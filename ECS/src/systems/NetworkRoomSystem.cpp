/*
** EPITECH PROJECT, 2023
** RType [WSL: Fedora]
** File description:
** '
*/

#include "NetworkRoomSystem.hpp"

inline void NetworkRoomSystem::Init(int port)
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
    _functions[10] = std::bind(&NetworkRoomSystem::shoot, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    _functions[11] = std::bind(&NetworkRoomSystem::move, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    _functions[12] = nullptr;
    _functions[13] = nullptr;
    _functions[14] = nullptr;
    return;
}

inline int NetworkRoomSystem::getClient(int id)
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

inline int NetworkRoomSystem::hourIntNow()
{
    auto currentTime = std::chrono::high_resolution_clock::now();
    auto timeSinceEpoch = currentTime.time_since_epoch();
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(timeSinceEpoch);
    int currentTime_ms = static_cast<int>(milliseconds.count());

    return currentTime_ms;
}

inline std::vector<int> NetworkRoomSystem::mergeVectors(const std::vector<int>& vec1, const std::vector<int>& vec2)
{
    std::vector<int> mergedVector = vec1;

    mergedVector.insert(mergedVector.end(), vec2.begin(), vec2.end());
    return mergedVector;
}

inline std::string NetworkRoomSystem::vectorToString(const std::vector<int>& data)
{
    std::stringstream ss;

    for (int num : data) {
        ss << static_cast<char>(num); // Conversion des entiers en caractères
    }

    std::string myString = ss.str();

    return myString;
}

inline std::vector<unsigned char> NetworkRoomSystem::encode(const std::vector<int>& values)
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

inline std::vector<int> NetworkRoomSystem::decode(const std::vector<unsigned char>& encodedData, size_t numBytesToRead)
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

inline unsigned short NetworkRoomSystem::findValidPort(asio::io_context& service)
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

inline void NetworkRoomSystem::sendDestroy(int entity)
{
    std::vector<int> data = {entity};
    int index = 0;

    for (auto client : _clients) {
        send({Action::DESTROY, 1}, data, true, client.getClientEndpoint(), index);
        index++;
    }
}

inline void NetworkRoomSystem::sendCreate(int entity, Coordinator &coordinator)
{
    auto& pos = coordinator.GetComponent<Position>(entity);
    auto& vel = coordinator.GetComponent<Velocity>(entity);
    auto& hitbox = coordinator.GetComponent<Hitbox>(entity);
    std::vector<int> res = {static_cast<int>(entity), static_cast<int>(pos._x * 10), static_cast<int>(pos._y * 10), static_cast<int>(vel._x * 10), static_cast<int>(vel._y * 10), static_cast<int>(hitbox._x * 10), static_cast<int>(hitbox._y * 10), static_cast<int>(hitbox.width * 10), static_cast<int>(hitbox.height * 10), hitbox.type};
    int index = 0;

    for (auto client : _clients) {
        send({Action::CREATE, 10}, res, true, client.getClientEndpoint(), index);
        index++;
    }
}

inline void NetworkRoomSystem::response(std::vector<int>& decodedIntegers, udp::endpoint& clientEndpoint, Coordinator &coordinator)
{
    (void)clientEndpoint;
    (void)coordinator;

    int timeStamp = decodedIntegers.at(0);
    int index = getClient(decodedIntegers.at(1));

    if (index == -1)
        return;
    _clients.at(index).delPacketSend(timeStamp);
    return;
}

inline void NetworkRoomSystem::connect(std::vector<int>& decodedIntegers, udp::endpoint& clientEndpoint, Coordinator &coordinator)
{
    std::string username = vectorToString(decodedIntegers);

    // std::cout << "username: " << username << std::endl;

    for (auto client : _clients) {
        if (client.getUsername() == username) {
            // std::vector<unsigned char> buffer = encode(_FAIL_CONNECT);
            // _socket.send_to(asio::buffer(buffer), clientEndpoint);
            return;
        }
    }

    Entity entity = coordinator.CreateEntity();

    coordinator.AddComponent<Position>(entity, {1, 0});
    coordinator.AddComponent<Velocity>(entity, {0, 0});
    coordinator.AddComponent<Hitbox>(entity, {0, 0, 1, 1, PLAYER});
    sendCreate(entity, coordinator);
    _clients.push_back(Client(username, clientEndpoint, entity));

    std::vector<int> tmp = {_clients.at(_clients.size() - 1).getID()};
    std::vector<unsigned char> buffer = encode(tmp);

    _socket.send_to(asio::buffer(buffer), clientEndpoint);
    sendEcs(coordinator);
}

inline void NetworkRoomSystem::ping(Coordinator &coordinator)
{

    for (auto client : _clients) {
        if (client.getAlive() == false) {
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

    int index = 0;
    int timeStamp = hourIntNow();

    for (auto client : _clients) {
        send(_PING, {timeStamp}, true, client.getClientEndpoint(), index);
        index++;
    }
}

inline void NetworkRoomSystem::pong(std::vector<int>& decodedIntegers, udp::endpoint& clientEndpoint, Coordinator &coordinator)
{
    (void)coordinator;

    int timeStamp = decodedIntegers.at(0);
    int index = getClient(decodedIntegers.at(1));

    if (index == -1) {
        return;
    }
    send({_OK}, {timeStamp}, false, clientEndpoint, index);
    _clients.at(index).delPacketSend(timeStamp);
    _clients.at(index).setAlive(true);
}

inline int NetworkRoomSystem::checkMove(Position& pos, Velocity& vel, Hitbox& hitbox, Entity entity, Coordinator& coordinator)
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

inline void NetworkRoomSystem::move(std::vector<int>& decodedIntegers, udp::endpoint& clientEndpoint, Coordinator &coordinator)
{
    int timeStamp = decodedIntegers.at(0);
    int index = getClient(decodedIntegers.at(1));

    if (index == -1)
        return;
    for (auto entity : this->_entities) {
        if (static_cast<int>(entity) == decodedIntegers.at(2)) {

            auto& vel = coordinator.GetComponent<Velocity>(entity);
            auto& pos = coordinator.GetComponent<Position>(entity);
            auto& hitbox = coordinator.GetComponent<Hitbox>(entity);

            if (checkMove(pos, vel, hitbox, entity, coordinator) == -1) {
                send(_UNVAILABLE_MOVE, {timeStamp}, false, _clients.at(index).getClientEndpoint(), index);
                return;
            }
            vel._x = decodedIntegers.at(3);
            vel._y = decodedIntegers.at(4);
            send(_PASS, {timeStamp}, false, _clients.at(index).getClientEndpoint(), index);
            return;
        }
    }

    std::vector<unsigned char> buffer = encode(_UNKNOW);

    _socket.send_to(asio::buffer(buffer), clientEndpoint);
}

inline void NetworkRoomSystem::shoot(std::vector<int>& decodedIntegers, udp::endpoint& clientEndpoint, Coordinator &coordinator)
{
    for (auto entity : this->_entities) {
        if (static_cast<int>(entity) == decodedIntegers.at(0)) {

            Entity bullet = coordinator.CreateEntity();

            coordinator.AddComponent<Position>(bullet, coordinator.GetComponent<Position>(decodedIntegers.at(0)));
            coordinator.AddComponent<Velocity>(bullet, {20, 0});
            coordinator.AddComponent<Hitbox>(bullet, {0, 0, 1, 1, BULLET});
            coordinator.AddComponent<Controllable>(bullet, {ENGINE});

            std::vector<unsigned char> buffer = encode(_PASS);

            _socket.send_to(asio::buffer(buffer), clientEndpoint);
            this->sendCreate(bullet, coordinator);
            return;
        }
    }

    std::vector<unsigned char> buffer = encode(_UNKNOW);

    _socket.send_to(asio::buffer(buffer), clientEndpoint);
}

inline int NetworkRoomSystem::checkAlreadyReceive(std::vector<int>& decodedIntegers, udp::endpoint clientEndpoint)
{
    int timeStamp = decodedIntegers.at(2);
    int index = getClient(decodedIntegers.at(3));

    if(index == -1)
        return -1;

    auto packets = _clients.at(index).getPacketsReceive();
    try {
        auto it = packets.at(timeStamp);
        send(_STOP_SEND, {timeStamp}, false, clientEndpoint, index);
        return -1;
    } catch (...) {
        return 0;
    }
}

inline void NetworkRoomSystem::handleCmd(std::vector<int>& decodedIntegers, udp::endpoint clientEndpoint, Coordinator &coordinator)
{
    int index = decodedIntegers.at(0);

    if (index < 0 || index > 15)
        return;
    if (index == 1) {
        _functions[index](decodedIntegers, clientEndpoint, coordinator);
        return;
    }
    if (decodedIntegers.size() < 4 && decodedIntegers.at(0) != 1)
        return;
    if (checkAlreadyReceive(decodedIntegers, clientEndpoint) == -1)
        return;

    int indexClient = getClient(decodedIntegers.at(3));

    _clients.at(indexClient).addPacketReceive(decodedIntegers.at(2), decodedIntegers);
    if (_functions[index] != nullptr) {
        decodedIntegers.erase(decodedIntegers.begin(), decodedIntegers.begin() + 2);
        _functions[index](decodedIntegers, clientEndpoint, coordinator);
    }
    else {
        // std::vector<unsigned char> buffer = encode(_UNKNOW);
        // _socket.send_to(asio::buffer(buffer), clientEndpoint);
    }
}

inline void NetworkRoomSystem::checkEvent(Coordinator &coordinator)
{
    while (1) {
        auto event = coordinator.GetEvent();

        if (event._type == Event::actions::EMPTY) {
            break;
        }
        if (event._type == Event::actions::SPAWN) {

            Entity ennemy = coordinator.CreateEntity();

            coordinator.AddComponent<Position>(ennemy, {1990, 0});
            coordinator.AddComponent<Velocity>(ennemy, {-20, 0});
            coordinator.AddComponent<Hitbox>(ennemy, {0, 0, 1, 1, ENNEMY});
            coordinator.AddComponent<Controllable>(ennemy, {IA});
            this->sendCreate(ennemy, coordinator);
            break;
        }
        if (event._type == Event::actions::DESTROY) {
            this->sendDestroy(event._entity);
        }
    }
}

inline void NetworkRoomSystem::processReceiveData(udp::endpoint clientEndpoint, Coordinator &coordinator, std::vector<int> res)
{
    if (clientEndpoint != asio::ip::udp::endpoint(asio::ip::make_address("0.0.0.0"), 0)) {
        handleCmd(res, clientEndpoint, coordinator);
    } else {
        return;
    }
}

inline void NetworkRoomSystem::sendEcs(Coordinator &coordinator)
{
    int index = 0;
    std::vector<int> header = {Cmd::POS, 1};

    for (auto client : _clients) {

        std::vector<int> encode_ = {};

        for (auto entity : this->_entities) {

            auto& pos = coordinator.GetComponent<Position>(entity);
            auto& vel = coordinator.GetComponent<Velocity>(entity);
            auto& hitbox = coordinator.GetComponent<Hitbox>(entity);
            std::vector<int> tmp = {static_cast<int>(entity), static_cast<int>(pos._x * 10), static_cast<int>(pos._y * 10), static_cast<int>(vel._x * 10), static_cast<int>(vel._y * 10), static_cast<int>(hitbox._x * 10), static_cast<int>(hitbox._y * 10), static_cast<int>(hitbox.width * 10), static_cast<int>(hitbox.height * 10), hitbox.type};

            encode_ = mergeVectors(encode_, tmp);
        }
        send(header, encode_, true, client.getClientEndpoint(), index);
        index++;
    }
}

inline void NetworkRoomSystem::send(std::vector<int> header, std::vector<int> data, bool stock, udp::endpoint client, int index)
{
    int timeStamp;

    if (stock == true) {
        timeStamp = hourIntNow();
        header.push_back(timeStamp);
    }

    std::vector<int> res = mergeVectors(header, data);
    std::vector<unsigned char> buffer = encode(res);

    _socket.send_to(asio::buffer(buffer), client);
    if (stock == true) {
        _clients.at(index).addPacketSend(timeStamp, buffer);
    }
    return;
}

inline std::tuple<std::vector<int>, udp::endpoint> NetworkRoomSystem::receive()
{
    std::vector<unsigned char> data(1024);
    udp::endpoint clientEndpoint;
    size_t length = _socket.receive_from(asio::buffer(data), clientEndpoint, 0);
    std::vector<int> decodedIntegers = decode(data, length);

    return std::make_tuple(decodedIntegers, clientEndpoint);
}

inline void NetworkRoomSystem::packetLoss()
{
    for (auto client : _clients) {

        auto packet = client.getPacketsSend();

        for (auto pair : packet) {
            _socket.send_to(asio::buffer(pair.second), client.getClientEndpoint());
        }
    }
}

inline void NetworkRoomSystem::Update(Coordinator& coordinator)
{
    std::vector<unsigned char> data(1024);
    std::chrono::seconds interval(5);
    std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
    std::chrono::steady_clock::duration elapsedTime = currentTime - _startTime;

    checkEvent(coordinator);
    if (elapsedTime >= interval) {
        packetLoss();
    }
    while (1) {
        try {
            std::vector<int> decodedIntegers;
            udp::endpoint clientEndpoint;
            std::tie(decodedIntegers, clientEndpoint) = receive();

            processReceiveData(clientEndpoint, coordinator, decodedIntegers);
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        } catch (...) {
            break;
        }
    }
    sendEcs(coordinator);
    if (elapsedTime >= interval) {
        ping(coordinator);
        _startTime = currentTime;
    }
    return;
}
