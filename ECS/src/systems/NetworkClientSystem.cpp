/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** NetworkClientSystem
*/

#include "NetworkClientSystem.hpp"
#include "components/Sprite.hpp"
#include "../components/Movable.hpp"
#include "../components/Controllable.hpp"
#include "../components/Hitbox.hpp"
#include "../components/HealthPoint.hpp"
#include "Graphic.hpp"

using asio::ip::udp;

#define CHECK_ZERO(x) x == 0 ? static_cast<float>(x) : static_cast<float>(x) / 10
// #define CHECK_ACTION(x) x == Event::MOVE ? 11 : 10
// #define CHECK_TYPE(x) x == 1 ? PLAYER : OTHER
#define CHECK_ACTION(x) x == Event::actions::MOVE ? 11 : 10

static HitboxType CHECK_TYPE(int x)
{
    if (x == 0)
        return ENNEMY;
    if (x == 1)
        return PLAYER;
    if (x == 2)
        return BULLET;
    return OTHER;
}

inline void NetworkClientSystem::Init(std::string host, std::string port, std::string name, int portClient)
{
    udp::endpoint endpoint(udp::v4(), portClient);

    _socket.close();
    _socket.open(endpoint.protocol());
    _socket.bind(endpoint);
    _id = -1;
    _serverEndpoint = udp::endpoint(asio::ip::make_address(host), atoi(port.c_str()));
    _username = name;
    send(_CONNECT, stringToVector(name), false);

    std::vector<unsigned char> data(1024);
    udp::endpoint receiveEndpoint;
    size_t length = _socket.receive_from(asio::buffer(data), receiveEndpoint, 0);
    std::vector<int> decodedIntegers = decode(data, length);

    _id = decodedIntegers.at(0);
    _functions[0] = std::bind(&NetworkClientSystem::response, this, std::placeholders::_1, std::placeholders::_2);
    _functions[1] = nullptr;
    _functions[2] = nullptr;
    _functions[3] = nullptr;
    _functions[4] = std::bind(&NetworkClientSystem::pos, this, std::placeholders::_1, std::placeholders::_2);
    _functions[5] = std::bind(&NetworkClientSystem::ping, this, std::placeholders::_1, std::placeholders::_2);
    _functions[6] = nullptr;
    _functions[7] = std::bind(&NetworkClientSystem::disconnect, this, std::placeholders::_1, std::placeholders::_2);
    _functions[8] = nullptr;
    _functions[9] = nullptr;
    _functions[10] = nullptr;
    _functions[11] = nullptr;
    _functions[12] = std::bind(&NetworkClientSystem::destroyEntity, this, std::placeholders::_1, std::placeholders::_2);
    _functions[13] = std::bind(&NetworkClientSystem::createEntity, this, std::placeholders::_1, std::placeholders::_2);
    _functions[14] = std::bind(&NetworkClientSystem::createRoom, this, std::placeholders::_1, std::placeholders::_2);
    _functions[15] = std::bind(&NetworkClientSystem::createMessage, this, std::placeholders::_1, std::placeholders::_2);
    _functions[16] = std::bind(&NetworkClientSystem::createSprite, this, std::placeholders::_1, std::placeholders::_2);
    _socket.non_blocking(true);
}

inline void NetworkClientSystem::addPacketSend(int timeStamp, std::vector<int> packet)
{
    _packetsSend[timeStamp] = packet;
}

inline void NetworkClientSystem::delPacketSend(int timeStamp)
{
    _packetsSend.erase(timeStamp);
}

inline void NetworkClientSystem::addPacketReceive(int timeStamp, std::vector<int> packet)
{
    _packetsReceive[timeStamp] = packet;
}

inline void NetworkClientSystem::delPacketReceive(int timeStamp)
{
    _packetsReceive.erase(timeStamp);
}

inline HitboxType NetworkClientSystem::deterType(int x)
{
    if (x == 1)
        return PLAYER;
    if (x == 0)
        return ENNEMY;
    return OTHER;
}

inline int NetworkClientSystem::hourIntNow()
{
    auto currentTime = std::chrono::high_resolution_clock::now();
    auto timeSinceEpoch = currentTime.time_since_epoch();
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(timeSinceEpoch);
    int currentTime_ms = static_cast<int>(milliseconds.count());

    return currentTime_ms;
}

inline std::vector<std::vector<int>> NetworkClientSystem::splitVector(const std::vector<int> &originalVector, size_t maxSize)
{
    std::vector<std::vector<int>> result;
    
    size_t startIndex = 0;

    while (startIndex < originalVector.size()) {

        size_t endIndex = startIndex + maxSize;

        if (endIndex >= originalVector.size()) {
            endIndex = originalVector.size();
        }

        std::vector<int> partie(originalVector.begin() + startIndex, originalVector.begin() + endIndex);

        if ((startIndex + maxSize) >= originalVector.size())
            result.push_back(partie);
        else {
            result.push_back(mergeVectors({-1}, partie));
        }
        startIndex = endIndex;
    }

    return result;
}

inline void NetworkClientSystem::createEntities(std::vector<int> decodedInteger, Coordinator &coordinator)
{
    decodedInteger.erase(decodedInteger.begin(), decodedInteger.begin() + 3);
    while (decodedInteger.empty() == false) {
        coordinator.AddEvent(Event{Event::CREATE, static_cast<Entity>(decodedInteger.at(0)), {std::make_any<int>(decodedInteger.at(0)), std::make_any<float>(CHECK_ZERO(decodedInteger.at(1))), std::make_any<float>(CHECK_ZERO(decodedInteger.at(2))), std::make_any<float>(CHECK_ZERO(decodedInteger.at(3))), std::make_any<float>(CHECK_ZERO(decodedInteger.at(4))), std::make_any<float>(CHECK_ZERO(decodedInteger.at(5))), std::make_any<float>(CHECK_ZERO(decodedInteger.at(6))), std::make_any<float>(CHECK_ZERO(decodedInteger.at(7))), std::make_any<float>(CHECK_ZERO(decodedInteger.at(8))), std::make_any<HitboxType>(CHECK_TYPE(decodedInteger.at(9))), std::make_any<int>(_id), std::make_any<int>(decodedInteger.at(10)), std::make_any<int>(decodedInteger.at(11)), std::make_any<int>(decodedInteger.at(12))}});
        //ADD INT FOR ID ENTITY
        // Entity entity = coordinator.CreateEntity(decodedInteger.at(0));
        // if (entity == _id) {
        //     coordinator.AddComponent<Movable>(entity, {NONE});
        // }
        // if (CHECK_TYPE(decodedInteger.at(9)) == PLAYER) {
        //     coordinator.AddComponent<Sprite>(entity, {Graphic::loadTexture("assets/spaceship.png")});
        // }
        // coordinator.AddComponent<Position>(entity, {CHECK_ZERO(decodedInteger.at(1)), CHECK_ZERO(decodedInteger.at(2))});
        // coordinator.AddComponent<Velocity>(entity, {CHECK_ZERO(decodedInteger.at(3)), CHECK_ZERO(decodedInteger.at(4))});
        // coordinator.AddComponent<Hitbox>(entity, {CHECK_ZERO(decodedInteger.at(5)), CHECK_ZERO(decodedInteger.at(6)), CHECK_ZERO(decodedInteger.at(7)), CHECK_ZERO(decodedInteger.at(8)), CHECK_TYPE(decodedInteger.at(9))});
        decodedInteger.erase(decodedInteger.begin(), decodedInteger.begin() + 13);
    }
}

inline unsigned short NetworkClientSystem::findValidPort(asio::io_context& service)
{
    udp::socket socket(service);
    unsigned short startingPort = 5000;
    unsigned short maxPort = 65535;

    for (unsigned short port = startingPort; port <= maxPort; ++port) {
        try {

            udp::endpoint endpoint(udp::v4(), port);

            socket.open(endpoint.protocol());
            socket.bind(endpoint);
            return port;
        } catch (std::exception&) {
        }
    }

    throw std::runtime_error("Tous les ports sont utilisés");
}

inline std::vector<int> NetworkClientSystem::mergeVectors(const std::vector<int>& vec1, const std::vector<int>& vec2)
{
    std::vector<int> mergedVector = vec1;

    mergedVector.insert(mergedVector.end(), vec2.begin(), vec2.end());
    return mergedVector;
}

inline std::vector<int> NetworkClientSystem::stringToVector(const std::string& str) {
    std::vector<int> result;

    for (char c : str) {
        result.push_back(static_cast<int>(c));
    }
    return result;
}

inline std::string NetworkClientSystem::vectorToString(const std::vector<int>& data)
{
    std::stringstream ss;

    for (int num : data) {
        ss << static_cast<char>(num); // Conversion des entiers en caractères
    }

    std::string myString = ss.str();

    return myString;
}

inline void NetworkClientSystem::response(std::vector<int>& decodedIntegers, Coordinator &coordinator)
{
    (void)coordinator;
    decodedIntegers.erase(decodedIntegers.begin(), decodedIntegers.begin() + 3);

    int timeStamp = decodedIntegers.at(0);

    _packetsSend.erase(timeStamp);
}

inline void NetworkClientSystem::ping(std::vector<int>& decodedIntegers, Coordinator &coordinator)
{
    (void)coordinator;
    decodedIntegers.erase(decodedIntegers.begin(), decodedIntegers.begin() + 2);
    std::vector<int> data = {_id};
    send(_PONG, data, true);
}

inline void NetworkClientSystem::disconnect(std::vector<int>& decodedIntegers, Coordinator &coordinator)
{
    (void)coordinator;
    decodedIntegers.erase(decodedIntegers.begin(), decodedIntegers.begin() + 2);

    int timeStamp = decodedIntegers.at(0);

    send(_OK, {timeStamp}, false);
    exit(0);
}

inline void NetworkClientSystem::pos(std::vector<int>& decodedIntegers, Coordinator &coordinator)
{
    decodedIntegers.erase(decodedIntegers.begin(), decodedIntegers.begin() + 2);

    int timeStamp = decodedIntegers.at(0);

    decodedIntegers.erase(decodedIntegers.begin(), decodedIntegers.begin() + 1);
    while (decodedIntegers.empty() == false) {
        for (auto entity : this->_entities) {
            if (static_cast<int>(entity) == decodedIntegers.at(0)) {
                auto& pos = coordinator.GetComponent<Position>(entity);
                auto& vel = coordinator.GetComponent<Velocity>(entity);
                auto& hitbox = coordinator.GetComponent<Hitbox>(entity);
                auto& health = coordinator.GetComponent<HealthPoint>(entity);

                pos._x = CHECK_ZERO(decodedIntegers.at(1));
                pos._y = CHECK_ZERO(decodedIntegers.at(2));
                vel._x = CHECK_ZERO(decodedIntegers.at(3));
                vel._y = CHECK_ZERO(decodedIntegers.at(4));
                hitbox._x = CHECK_ZERO(decodedIntegers.at(5));
                hitbox._y = CHECK_ZERO(decodedIntegers.at(6));
                hitbox.width = CHECK_ZERO(decodedIntegers.at(7));
                hitbox.height = CHECK_ZERO(decodedIntegers.at(8));
                hitbox.type = deterType(decodedIntegers.at(9));
                health._max_hp = decodedIntegers.at(10);
                health._curr_hp = decodedIntegers.at(11);
                break;
            }
        }
        decodedIntegers.erase(decodedIntegers.begin(), decodedIntegers.begin() + 13);
    }
    send(_OK, {timeStamp}, false);
}

inline void NetworkClientSystem::createSprite(std::vector<int>& decodedIntegers, Coordinator& coordinator)
{
    decodedIntegers.erase(decodedIntegers.begin(), decodedIntegers.begin() + 2);

    int timeStamp = decodedIntegers.at(0);
    int index = decodedIntegers.at(1);
    int size = decodedIntegers.at(2);

    decodedIntegers.erase(decodedIntegers.begin(), decodedIntegers.begin() + 3);

    send(_OK, {timeStamp}, false);

    std::vector<int> base64 = {};
    std::vector<int> filePath = {};

    int y = 0;
    for (auto i : decodedIntegers) {
        if (y == size)
            break;
        base64.push_back(i);
        y++;
    }
    for (size_t i = base64.size(); i < decodedIntegers.size(); ++i)
        filePath.push_back(decodedIntegers[i]);
    coordinator.AddEvent(Event{Event::actions::CREATE_SPRITE, 0, {std::make_any<std::string>(vectorToString(base64)), std::make_any<std::string>(vectorToString(filePath)), std::make_any<int>(index)}});
}

inline void NetworkClientSystem::createMessage(std::vector<int>& decodedIntegers, Coordinator& coordinator)
{
    decodedIntegers.erase(decodedIntegers.begin(), decodedIntegers.begin() + 2);

    int timeStamp = decodedIntegers.at(0);

    decodedIntegers.erase(decodedIntegers.begin(), decodedIntegers.begin() + 1);

    std::string message = vectorToString(decodedIntegers);
    size_t position = message.find(':');
    std::string user = message.substr(0, position);
    std::string msg = message.substr(position + 1);

    send(_OK, {timeStamp}, false);
    coordinator.AddEvent(Event{Event::actions::CREATE_MESSAGE, 0, {std::make_any<std::string>(user), std::make_any<std::string>(msg)}});
}

inline void NetworkClientSystem::createRoom(std::vector<int>& decodedIntegers, Coordinator &coordinator)
{
    (void)coordinator;
    decodedIntegers.erase(decodedIntegers.begin(), decodedIntegers.begin() + 2);

    int timeStamp = decodedIntegers.at(0);

    decodedIntegers.erase(decodedIntegers.begin(), decodedIntegers.begin() + 1);

    int port = decodedIntegers.at(0);
    int nbPlayer = decodedIntegers.at(1);

    decodedIntegers.erase(decodedIntegers.begin(), decodedIntegers.begin() + 2);

    std::string name = vectorToString(decodedIntegers);
    std::ofstream fichier;

    fichier.open("room.txt", std::ios::app);
    if (fichier.is_open()) {
        fichier << std::to_string(port) << "\t" << name << "\t" << std::to_string(nbPlayer) << std::endl;
        fichier.close();
        send({_OK}, {timeStamp}, false);
    } else {
        std::cerr << "Impossible d'ouvrir le fichier." << std::endl;
        send({_CREATE_ROOM}, {timeStamp}, false);
    }
}

inline void NetworkClientSystem::createEntity(std::vector<int> decodedIntegers, Coordinator &coordinator)
{
    decodedIntegers.erase(decodedIntegers.begin(), decodedIntegers.begin() + 2);

    int timeStamp = decodedIntegers.at(0);

    decodedIntegers.erase(decodedIntegers.begin(), decodedIntegers.begin() + 1);
    while (decodedIntegers.empty() == false) {
        coordinator.AddEvent(Event{Event::CREATE, static_cast<Entity>(decodedIntegers.at(0)), {std::make_any<int>(decodedIntegers.at(0)), std::make_any<float>(CHECK_ZERO(decodedIntegers.at(1))), std::make_any<float>(CHECK_ZERO(decodedIntegers.at(2))), std::make_any<float>(CHECK_ZERO(decodedIntegers.at(3))), std::make_any<float>(CHECK_ZERO(decodedIntegers.at(4))), std::make_any<float>(CHECK_ZERO(decodedIntegers.at(5))), std::make_any<float>(CHECK_ZERO(decodedIntegers.at(6))), std::make_any<float>(CHECK_ZERO(decodedIntegers.at(7))), std::make_any<float>(CHECK_ZERO(decodedIntegers.at(8))), std::make_any<HitboxType>(CHECK_TYPE(decodedIntegers.at(9))), std::make_any<int>(_id), std::make_any<int>(decodedIntegers.at(10)), std::make_any<int>(decodedIntegers.at(11)), std::make_any<int>(decodedIntegers.at(12))}});
        decodedIntegers.erase(decodedIntegers.begin(), decodedIntegers.begin() + 13);
    }
    send(_OK, {timeStamp}, false);
}

inline void NetworkClientSystem::destroyEntity(std::vector<int> decodedIntegers, Coordinator &coordinator)
{
    decodedIntegers.erase(decodedIntegers.begin(), decodedIntegers.begin() + 2);

    int timeStamp = decodedIntegers.at(0);

    decodedIntegers.erase(decodedIntegers.begin(), decodedIntegers.begin() + 1);
    send(_OK, {timeStamp}, false);
    coordinator.AddEvent(Event{Event::DESTROY, static_cast<Entity>(decodedIntegers.at(0)), {std::make_any<int>(decodedIntegers.at(0))}});
}

inline void NetworkClientSystem::handleCmd(std::vector<int>& decodedIntegers, Coordinator &coordinator)
{
    int index = decodedIntegers.at(0);

    if (index < 0 || index > 16)
        return;
    if (decodedIntegers.size() < 3)
        return;
    if (checkAlreadyReceive(decodedIntegers) == -1)
        return;
    _packetsReceive[decodedIntegers.at(2)] = decodedIntegers;
    if (_functions[index] != nullptr) {
        _functions[index](decodedIntegers, coordinator);
    }
    else {
        send(_UNKNOW, {}, false);
    }
}

inline std::vector<unsigned char> NetworkClientSystem::encode(const std::vector<int>& values)
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

inline std::vector<int> NetworkClientSystem::decode(const std::vector<unsigned char>& encodedData, size_t numBytesToRead)
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

inline void NetworkClientSystem::paramEvent(Event& event)
{
    std::vector<std::string> list;
    int selectBullet = std::any_cast<int>(event._data.at(0));
    int selectEnnemy = std::any_cast<int>(event._data.at(1));
    int selectEnnemyTwo = std::any_cast<int>(event._data.at(2));
    int selectEnnemyElite = std::any_cast<int>(event._data.at(3));
    int selectEnnemyBoss = std::any_cast<int>(event._data.at(4));
    int selectEnnemyBullet = std::any_cast<int>(event._data.at(5));

    for (std::size_t i = 6; i < event._data.size(); i++)
        list.push_back(std::any_cast<std::string>(event._data[i]));
    // int port = atoi(list.at(0).c_str());
    int nbPlayer = atoi(list.at(2).c_str());

    std::vector<int> header = {PARAM, 3};
    std::vector<int> data = {nbPlayer, selectBullet, selectEnnemy, selectEnnemyTwo, selectEnnemyElite, selectEnnemyBoss, selectEnnemyBullet};
    std::vector<int> name = stringToVector(list.at(1));

    data = mergeVectors(data, name);
    send(header, data, true);
    return;
}

inline void NetworkClientSystem::joinEvent(Event& event, Coordinator& coordinator)
{
    std::vector<std::string> list;
    int selectSprite = std::any_cast<int>(event._data[0]);

    for (std::size_t i = 1; i < event._data.size(); i++)
        list.push_back(std::any_cast<std::string>(event._data[i]));
    _serverEndpoint = udp::endpoint(asio::ip::make_address(list.at(0)), atoi(list.at(1).c_str()));
    std::vector<int> header = {CONNECT, 1};

    if (list.at(3) == "true") {
        send(header, mergeVectors({selectSprite}, stringToVector("(S) " + _username)), false);
    }
    else {
        send(header, mergeVectors({selectSprite}, stringToVector(_username)), false);
    }

    _socket.non_blocking(false);

    std::vector<unsigned char> data(1024);
    udp::endpoint receiveEndpoint;
    size_t length;

    while (1) {
        try {
            length = _socket.receive_from(asio::buffer(data), receiveEndpoint, 0);
            if (receiveEndpoint == _serverEndpoint)
                break;
        } catch (...) {
            send(header, stringToVector(list.at(2)), false);
        }   
    }
    std::vector<int> decodedIntegers = decode(data, length);

    _id = decodedIntegers.at(0);
    send(_OK, {decodedIntegers.at(0)}, false);
    while (1) {
        try {
            length = _socket.receive_from(asio::buffer(data), receiveEndpoint, 0);
            if (receiveEndpoint == _serverEndpoint)
                break;
        } catch (...) {
        }
           
    }
    decodedIntegers = decode(data, length);
    createEntities(decodedIntegers, coordinator);
    _socket.non_blocking(true);
    return;
}

inline void NetworkClientSystem::moveEvent(Event& event)
{
    send({CHECK_ACTION(event._type), 3}, {static_cast<int>(event._entity), static_cast<int>(std::any_cast<Velocity>(event._data.at(0))._x * 10), static_cast<int>(std::any_cast<Velocity>(event._data.at(0))._y * 10)}, true);
}

inline void NetworkClientSystem::messageEvent(Event& event)
{
    send({event._type, 1}, stringToVector(std::any_cast<std::string>(event._data.at(0))), true);
}

inline void NetworkClientSystem::spriteEvent(Event& event)
{
    std::vector<int> data = stringToVector(std::any_cast<std::string>(event._data.at(0)));
    std::vector<int> name = stringToVector(std::any_cast<std::string>(event._data.at(1)));

    data = mergeVectors({static_cast<int>(data.size())}, data);
    data = mergeVectors(data, name);
    send({event._type, 1}, data, true);
}

inline void NetworkClientSystem::checkEvent(Coordinator &coordinator)
{
    while (1) {
        auto event = coordinator.GetEvent();

        if (event._type == Event::EMPTY) {
            break;
        }
        if (event._type == Event::MESSAGE) {
            messageEvent(event);
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        if (event._type == Event::MOVE) {
            moveEvent(event);
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        if (event._type == Event::PARAM) {
            paramEvent(event);
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            return;
        }
        if (event._type == Event::JOIN) {
            joinEvent(event, coordinator);
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            return;
        }
        if (event._type == Event::SEND_SPRITE) {
            spriteEvent(event);
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        if (event._type == Event::actions::SHOOT) {
            for (auto entity : _entities) {
                if (this->_id == static_cast<int>(entity)) {
                    send({CHECK_ACTION(event._type), 1}, {static_cast<int>(entity)}, true);
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));
                    break;
                }
            }
        }
    }
}


inline void NetworkClientSystem::send(std::vector<int> header, std::vector<int> data, bool stock)
{
    int timeStamp;

    if (stock == true) {
        timeStamp = hourIntNow();
        header.push_back(timeStamp);
    }
    header.push_back(_id);

    std::vector<int> res = mergeVectors(header, data);
    if (res.size() > 500) {
        std::vector<unsigned char> buffer;
        std::vector<std::vector<int>> data = splitVector(res, 500);

        for (size_t i = 0; i < data.size(); i++) {
            buffer = encode(data.at(i));
            _socket.send_to(asio::buffer(buffer), _serverEndpoint);
        }
        if (stock == true) {
            _packetsSend[timeStamp] = res;
        }
    } else {
        std::vector<unsigned char> buffer = encode(res);

        _socket.send_to(asio::buffer(buffer), _serverEndpoint);
        if (stock == true) {
            _packetsSend[timeStamp] = res;
        }
    }
}

inline std::vector<int> NetworkClientSystem::receive()
{
    std::vector<unsigned char> data(15000);
    udp::endpoint receiveEndpoint;
    size_t length = _socket.receive_from(asio::buffer(data), receiveEndpoint, 0);
    std::vector<int> split = {};

    if (receiveEndpoint != _serverEndpoint)
        throw std::runtime_error("Bad Ip");

    std::vector<int> decodedIntegers = decode(data, length);
    int block = 0;

    if (decodedIntegers.at(0) == -1) {
        block = -1;
        decodedIntegers.erase(decodedIntegers.begin(), decodedIntegers.begin() + 1);
    }
    while (block == -1) {
        data.clear();
        std::vector<unsigned char> dataBis(15000);
        udp::endpoint clientEndpointBis;
        _socket.non_blocking(false);
        length = _socket.receive_from(asio::buffer(dataBis),clientEndpointBis, 0);
        _socket.non_blocking(true);
        split = decode(dataBis, length);
        if (split.at(0) == -1) {
            split.erase(split.begin(), split.begin() + 1);
            decodedIntegers = mergeVectors(decodedIntegers, split);
        } else {
            decodedIntegers = mergeVectors(decodedIntegers, split);
            block = 0;
        }
    }
    _packetsReceive[decodedIntegers.at(2)] = decodedIntegers;

    data.clear();
    return decodedIntegers;
}

inline void NetworkClientSystem::packetLoss()
{
    for (auto pair : _packetsSend) {
        _socket.send_to(asio::buffer(pair.second), _serverEndpoint);
    }
}

inline int NetworkClientSystem::checkAlreadyReceive(std::vector<int> decodedIntegers)
{
    int timeStamp = decodedIntegers.at(2);
    auto it = _packetsReceive.find(timeStamp);

    if (it != _packetsReceive.end()) {
        //std::cout << "Error: Key not found" << std::endl;
        return 0;
    } else {
        send(_STOP_SEND, {timeStamp}, false);
        return -1;
    }
    return 0;
}

inline void NetworkClientSystem::Update(Coordinator &coordinator)
{
    std::chrono::seconds interval(5);
    std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
    std::chrono::steady_clock::duration elapsedTime = currentTime - _startTime;

    checkEvent(coordinator);
    if (elapsedTime >= interval) {
        packetLoss();
        _startTime = currentTime;
    }
    while (1) {
        try {
            std::vector<int> decodedIntegers = receive();
    
            handleCmd(decodedIntegers, coordinator);
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        } catch (...) {
            //e.what();
            break;
        }
    }
}