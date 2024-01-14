/*
** EPITECH PROJECT, 2023
** RType [WSL: Fedora]
** File description:
** '
*/

#include "NetworkRoomSystem.hpp"

inline void NetworkRoomSystem::Init(int port, udp::endpoint clientEndpoint, std::string nameAdmin, int nbPLayer, std::map<int, std::tuple<std::string, std::string>> sprite, std::vector<int> selectSprites)
{
    udp::endpoint endpoint(udp::v4(), port);

    _spriteEnnemyTwo = selectSprites.at(2);
    _spriteEnnemyElite = selectSprites.at(3);
    _spriteEnnemyBoss = selectSprites.at(4);
    _spriteEnnemyBullet = selectSprites.at(5);
    _sprite = sprite;
    setDefaultPath();
    if (selectSprites.at(0) == -1) {
        _spriteBullet = _pathDefault.at(2);
    } else {
        _spriteBullet = selectSprites.at(0);
    }
    if (selectSprites.at(1) == -1) {
        _spriteEnnemy = _pathDefault.at(1);
    } else {
        _spriteEnnemy = selectSprites.at(1);
    }
    if (selectSprites.at(2) == -1) {
        _spriteEnnemyTwo = _pathDefault.at(3);
    } else {
        _spriteEnnemyTwo = selectSprites.at(1);
    }
    if (selectSprites.at(3) == -1) {
        _spriteEnnemyElite = _pathDefault.at(4);
    } else {
        _spriteEnnemyElite = selectSprites.at(1);
    }
    if (selectSprites.at(4) == -1) {
        _spriteEnnemyBoss = _pathDefault.at(5);
    } else {
        _spriteEnnemyBoss = selectSprites.at(1);
    }
    if (selectSprites.at(5) == -1) {
        _spriteEnnemyBullet = _pathDefault.at(6);
    } else {
        _spriteEnnemyBullet = selectSprites.at(1);
    }
    _nbPLayer = nbPLayer;
    _admin = std::make_tuple(clientEndpoint, nameAdmin);
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
    _functions[15] = std::bind(&NetworkRoomSystem::message, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    _functions[16] = std::bind(&NetworkRoomSystem::sprite, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    return;
}

inline void NetworkRoomSystem::setDefaultPath(void)
{
    int index = 0; 
    for (auto sprite : _sprite) {
        if (std::get<1>(sprite.second) == "./assets/sprite/spaceship.png")
            _pathDefault.push_back(index);
        index++;
    }
    index = 0;
    for (auto sprite : _sprite) {
        if (std::get<1>(sprite.second) == "./assets/sprite/carli.png") {
            _pathDefault.push_back(index);
        }
        index++;
    }
    index = 0;
    for (auto sprite : _sprite) {
        if (std::get<1>(sprite.second) == "./assets/sprite/bullets.png")
            _pathDefault.push_back(index);
        index++;
    }
    index = 0;
    for (auto sprite : _sprite) {
        if (std::get<1>(sprite.second) == "./assets/sprite/ludo.png")
            _pathDefault.push_back(index);
        index++;
    }
    index = 0;
    for (auto sprite : _sprite) {
        if (std::get<1>(sprite.second) == "./assets/sprite/slimane.png")
            _pathDefault.push_back(index);
        index++;
    }
    index = 0;
    for (auto sprite : _sprite) {
        if (std::get<1>(sprite.second) == "./assets/sprite/kev_boss.png")
            _pathDefault.push_back(index);
        index++;
    }
    index = 0;
    for (auto sprite : _sprite) {
        if (std::get<1>(sprite.second) == "./assets/sprite/enn_bullets.png")
            _pathDefault.push_back(index);
        index++;
    }
    index = 0;
}

inline int NetworkRoomSystem::getClient(int id)
{
    int index = 0;

    for (auto client : _clients) {
        if (id == client.getID()) {
            return index;
        }
        index++;
    }
    return -1;
}

inline int NetworkRoomSystem::hourIntNow()
{
    auto currentTime = std::chrono::steady_clock::now();
    auto timeSinceEpoch = currentTime.time_since_epoch();
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(timeSinceEpoch);
    int currentTime_ms = static_cast<int>(milliseconds.count());

    return currentTime_ms;
}

inline std::vector<std::vector<int>> NetworkRoomSystem::splitVector(const std::vector<int> &originalVector, size_t maxSize)
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

inline std::vector<int> NetworkRoomSystem::mergeVectors(const std::vector<int>& vec1, const std::vector<int>& vec2)
{
    std::vector<int> mergedVector = vec1;

    mergedVector.insert(mergedVector.end(), vec2.begin(), vec2.end());
    return mergedVector;
}

inline std::vector<int> NetworkRoomSystem::stringToVector(const std::string& str) 
{
    std::vector<int> result;

    for (char c : str) {
        result.push_back(static_cast<int>(c));
    }
    return result;
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

inline void NetworkRoomSystem::sendCreate(int entity, Coordinator &coordinator, int selectSprite)
{
    auto& pos = coordinator.GetComponent<Position>(entity);
    auto& vel = coordinator.GetComponent<Velocity>(entity);
    auto& hitbox = coordinator.GetComponent<Hitbox>(entity);
    auto& health = coordinator.GetComponent<HealthPoint>(entity);

    int scale = selectSprite == _spriteEnnemyBoss ? 2 : 1;

    std::vector<int> res = {static_cast<int>(entity), static_cast<int>(pos._x * 10), static_cast<int>(pos._y * 10), static_cast<int>(vel._x * 10), static_cast<int>(vel._y * 10), static_cast<int>(hitbox._x * 10), static_cast<int>(hitbox._y * 10), static_cast<int>(hitbox.width * 10), static_cast<int>(hitbox.height * 10), hitbox.type, static_cast<int>(health._max_hp), static_cast<int>(health._curr_hp), selectSprite, scale * 10};

    int index = 0;

    for (auto client : _clients) {
        send({Action::CREATE, 10}, res, true, client.getClientEndpoint(), index);
        index++;
    }
}

inline int NetworkRoomSystem::checkCmdMessage(std::string msg, int index, udp::endpoint& clientEndpoint)
{
    if (index == -1) {
        return -1;
    }

    std::string kickCommand = "/kick";
    std::string banCommand = "/ban";
    size_t kickPosition = msg.find(kickCommand);
    size_t banPosition = msg.find(banCommand);

    if (kickPosition != std::string::npos) {
        if (clientEndpoint != std::get<0>(_admin) || _clients.at(index).getUsername() != std::get<1>(_admin)) {
            std::string error = "System: You don't have permission";
            send({MESSAGE_SEND, 1}, stringToVector(error), true, clientEndpoint, index);
            return -1;
        }

        std::string pseudo = msg.substr(kickPosition + kickCommand.length() + 1);
        std::string msgSystem = "System: " + pseudo + " has been kick to the room";
        int error = -1;
        int i = 0;

        for (auto client : _clients) {
            if (client.getUsername() == pseudo) {
                error = 0;
            }
            i++;
        }
        if (error == -1) {
            std::string error = "System: You enter wrong username";
            send({MESSAGE_SEND, 1}, stringToVector(error), true, clientEndpoint, index);
            return -1;
        }
        i = 0;
        for (auto client : _clients) {
            if (client.getUsername() == pseudo) {
                send({DISCONNECT, 1}, {}, true, client.getClientEndpoint(), i);
            } else {
                send({MESSAGE_SEND, 1}, stringToVector(msgSystem), true, client.getClientEndpoint(), i);
            }
            i++;
        }
        return -1;
    }

    if (banPosition != std::string::npos) {
        if (clientEndpoint != std::get<0>(_admin) || _clients.at(index).getUsername() != std::get<1>(_admin)) {
            std::string error = "System: You don't have permission";
            send({MESSAGE_SEND, 1}, stringToVector(error), true, clientEndpoint, index);
            return -1;
        }

        std::string pseudo = msg.substr(banPosition + banCommand.length() + 1);
        std::string msgSystem = "System: " + pseudo + " has been ban to the room";
        int error = -1;
        int i = 0;

        for (auto client : _clients) {
            if (client.getUsername() == pseudo) {
                error = 0;
            }
            i++;
        }
        if (error == -1) {
            std::string error = "System: You enter wrong username";
            send({MESSAGE_SEND, 1}, stringToVector(error), true, clientEndpoint, index);
            return -1;
        }
        i = 0;
        for (auto client : _clients) {
            if (client.getUsername() == pseudo) {
                _ban.push_back(client.getClientEndpoint());
                send({DISCONNECT, 1}, {}, true, client.getClientEndpoint(), i);
            } else {
                send({MESSAGE_SEND, 1}, stringToVector(msgSystem), true, client.getClientEndpoint(), i);
            }
            i++;
        }
        return -1;
    }
    return 0;
}

inline void NetworkRoomSystem::message(std::vector<int>& decodedIntegers, udp::endpoint& clientEndpoint, Coordinator &coordinator)
{
    (void)coordinator;
    int timeStamp = decodedIntegers.at(0);

    decodedIntegers.erase(decodedIntegers.begin(), decodedIntegers.begin() + 1);

    int index = getClient(decodedIntegers.at(0));

    decodedIntegers.erase(decodedIntegers.begin(), decodedIntegers.begin() + 1);

    std::string message = vectorToString(decodedIntegers);

    send(_OK, {timeStamp}, false, clientEndpoint, index);

    if (checkCmdMessage(message, index, clientEndpoint) == -1) {
        return;
    }

    std::string res = _clients.at(index).getUsername() + ": " + message;
    int i = 0;

    for (auto client : _clients) {
        send({MESSAGE_SEND, 1}, stringToVector(res), true, client.getClientEndpoint(), i);
        i++;
    }
}

inline void NetworkRoomSystem::sprite(std::vector<int>& decodedIntegers, udp::endpoint& clientEndpoint, Coordinator &coordinator)
{
    (void)clientEndpoint;
    (void)coordinator;

    int index = decodedIntegers.at(0);
    int size = decodedIntegers.at(1);

    decodedIntegers.erase(decodedIntegers.begin(), decodedIntegers.begin() + 2);

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
    _sprite[index] = std::make_tuple(vectorToString(base64), vectorToString(filePath));
    int i = 0;
    for (auto client : _clients) {
        send({SPRITE, 3}, mergeVectors({index, size}, decodedIntegers), true, client.getClientEndpoint(), i);
        i++;
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
    int selectSprite = decodedIntegers.at(0);

    decodedIntegers.erase(decodedIntegers.begin(), decodedIntegers.begin() + 1);

    std::string username = vectorToString(decodedIntegers);
    for (auto client : _clients) {
        if (client.getUsername() == username) {
            return;
        }
    }

    int i = 0;
    std::string msgSystem = "System: " + username + " connected to the room";

    for (auto client : _clients) {
        send({MESSAGE_SEND, 1}, stringToVector(msgSystem), true, client.getClientEndpoint(), i);
        i++;
    }

    Entity entity = coordinator.CreateEntity();

    coordinator.AddComponent<Position>(entity, {1, 0});
    coordinator.AddComponent<Velocity>(entity, {0, 0});
    if (username.length() > 4 && username.substr(0, 4) == "(S) ")
        coordinator.AddComponent<Hitbox>(entity, {0, 0, 0, 0, SPECTATOR});
    else
        coordinator.AddComponent<Hitbox>(entity, {0, 0, 100, 100, PLAYER});
    coordinator.AddComponent<HealthPoint>(entity, {3, 3});
    coordinator.AddComponent<Damage>(entity, {1, 1});
    if (selectSprite == -1)
        selectSprite = _pathDefault.at(0);
    sendCreate(entity, coordinator, selectSprite);
    _clients.push_back(Client(username, clientEndpoint, entity, selectSprite));

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
    int timeStamp = decodedIntegers.at(0);

    decodedIntegers.erase(decodedIntegers.begin(), decodedIntegers.begin() + 1);

    int index = getClient(decodedIntegers.at(0));

    for (auto entity : this->_entities) {
        if (static_cast<int>(entity) == decodedIntegers.at(0)) {

            Entity bullet = coordinator.CreateEntity();

            coordinator.AddComponent<Position>(bullet, coordinator.GetComponent<Position>(decodedIntegers.at(0)));
            coordinator.AddComponent<Velocity>(bullet, {20, 0});
            coordinator.AddComponent<Hitbox>(bullet, {0, 0, 60, 60, BULLET});
            coordinator.AddComponent<Damage>(bullet, {1, 1});
            coordinator.AddComponent<HealthPoint>(bullet, {1, 1});
            coordinator.AddComponent<Controllable>(bullet, {ENGINE});

            send(_PASS, {timeStamp}, false, clientEndpoint, index);
            this->sendCreate(bullet, coordinator, _spriteBullet);
            return;
        }
    }
    send(_UNKNOW, {timeStamp}, false, clientEndpoint, index);
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

    if (index < 0 || index > 16)
        return;
    if (index == 1) {
        decodedIntegers.erase(decodedIntegers.begin(), decodedIntegers.begin() + 3);
        _functions[index](decodedIntegers, clientEndpoint, coordinator);
        return;
    }
    if (index == 16) {
        decodedIntegers.erase(decodedIntegers.begin(), decodedIntegers.begin() + 2);
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
            int enn_sprite = _spriteEnnemyBullet;
            int check = 1;
            if (event._entity != 0) {
                check = 0;
                for (auto entity : this->_entities) {
                    auto& hit = coordinator.GetComponent<Hitbox>(entity);
                    if (entity == event._entity && hit.type == ENNEMY && hit.height != 51)
                        check = 1;
                }
            }
            if (check == 0)
                break;
            Entity ennemy = coordinator.CreateEntity();
            int ennemy_check = static_cast<int>(std::any_cast<int>(event._data[9]));
            coordinator.AddComponent<Position>(ennemy, {(static_cast<float>(std::any_cast<float>(event._data[1]))), (static_cast<float>(std::any_cast<int>(event._data[0])))});
            coordinator.AddComponent<Velocity>(ennemy, {(static_cast<float>(std::any_cast<float>(event._data[2]))), 0});
            coordinator.AddComponent<Hitbox>(ennemy, {(static_cast<float>(std::any_cast<float>(event._data[3]))), (static_cast<float>(std::any_cast<float>(event._data[4]))), (static_cast<float>(std::any_cast<float>(event._data[5]))), (static_cast<float>(std::any_cast<float>(event._data[6]))), ENNEMY});
            coordinator.AddComponent<Controllable>(ennemy, {IA});
            coordinator.AddComponent<HealthPoint>(ennemy, {(static_cast<int>(std::any_cast<int>(event._data[7]))), (static_cast<int>(std::any_cast<int>(event._data[7])))});
            coordinator.AddComponent<Damage>(ennemy, {(static_cast<int>(std::any_cast<int>(event._data[8]))), (static_cast<int>(std::any_cast<int>(event._data[8])))});
            if (ennemy_check != 0) {
                coordinator.AddComponent<SpawnClock>(ennemy, {std::chrono::steady_clock::now(), std::chrono::steady_clock::now(), 0, 60, 61});
                coordinator.AddComponent<SpawnInfo>(ennemy, {2, 0, 0, -20, 0, 0, 51, 51, 1, 1, 0});
                enn_sprite = _spriteEnnemy;
            }
            if (ennemy_check == 2)
                enn_sprite = _spriteEnnemyTwo;
            if (ennemy_check == 3)
                enn_sprite = _spriteEnnemyElite;
            if (ennemy_check == 4) {
                coordinator.AddComponent<StaticType>(ennemy, {1700, 3});
                enn_sprite = _spriteEnnemyBoss;
            }
            this->sendCreate(ennemy, coordinator, enn_sprite);
            break;
        }
        if (event._type == Event::actions::DESTROY) {
            this->sendDestroy(event._entity);
            coordinator.DestroyEntity(event._entity);
            break;
        }
    }
}

inline void NetworkRoomSystem::processReceiveData(udp::endpoint clientEndpoint, Coordinator &coordinator, std::vector<int> res)
{
    for (auto i : _ban) {
        if (i == clientEndpoint)
            return;
    }
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
            auto& health = coordinator.GetComponent<HealthPoint>(entity);
            int selectSprite = -1;
            int scale = 1;

            for (auto clientBis : _clients) {
                if (static_cast<int>(entity) == clientBis.getID()) {
                    selectSprite = clientBis.getSprite();
                    break;
                }
            }
            std::vector<int> tmp = {static_cast<int>(entity), static_cast<int>(pos._x * 10), static_cast<int>(pos._y * 10), static_cast<int>(vel._x * 10), static_cast<int>(vel._y * 10), static_cast<int>(hitbox._x * 10), static_cast<int>(hitbox._y * 10), static_cast<int>(hitbox.width * 10), static_cast<int>(hitbox.height * 10), hitbox.type, static_cast<int>(health._max_hp), static_cast<int>(health._curr_hp), static_cast<int>(selectSprite), scale * 10};

            encode_ = mergeVectors(encode_, tmp);
        }
        send(header, encode_, true, client.getClientEndpoint(), index);
        index++;
    }
}

inline void NetworkRoomSystem::send(std::vector<int> header, std::vector<int> data, bool stock, udp::endpoint client, int index)
{
    int timeStamp = 0;

    if (stock == true) {
        timeStamp = hourIntNow();
        header.push_back(timeStamp);
    }

    std::vector<int> res = mergeVectors(header, data);
    if (res.size() > 500) {
        std::vector<unsigned char> buffer;
        std::vector<std::vector<int>> data = splitVector(res, 500);

        for (size_t i = 0; i < data.size(); i++) {
            buffer = encode(data.at(i));
            _socket.send_to(asio::buffer(buffer), client);
        }
    } else {
        std::vector<unsigned char> buffer = encode(res);

        _socket.send_to(asio::buffer(buffer), client);
        if (stock == true) {
            _clients.at(index).addPacketSend(timeStamp, buffer);
        }
        buffer.clear();
    }
    return;
}

inline std::tuple<std::vector<int>, udp::endpoint> NetworkRoomSystem::receive()
{
    std::vector<unsigned char> data(15000);
    udp::endpoint clientEndpoint;
    size_t length = _socket.receive_from(asio::buffer(data), clientEndpoint, 0);
    std::vector<int> decodedIntegers = decode(data, length);
    std::vector<int> split = {};
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
    data.clear();
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
