/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** NetworkServerSystem
*/

#include "NetworkServerSystem.hpp"

inline void NetworkServerSystem::Init(std::map<int, std::tuple<std::string, std::string>> sprite)
{
    udp::endpoint endpoint(udp::v4(), 4242);

    _sprite = sprite;
    _socket.close();
    _socket.open(endpoint.protocol());
    _socket.bind(endpoint);
    _socket.non_blocking(true);
    _functions[0] = std::bind(&NetworkServerSystem::response, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    _functions[1] = std::bind(&NetworkServerSystem::connect, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    _functions[2] = std::bind(&NetworkServerSystem::param, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    _functions[3] = nullptr;
    _functions[4] = nullptr;
    _functions[5] = nullptr;
    _functions[6] = std::bind(&NetworkServerSystem::pong, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    _functions[7] = nullptr;
    _functions[8] = nullptr;
    _functions[9] = nullptr;
    _functions[10] = nullptr;
    _functions[11] = nullptr;
    _functions[12] = nullptr;
    _functions[13] = nullptr;
    _functions[14] = nullptr;
    _functions[15] = nullptr;
    _functions[16] = std::bind(&NetworkServerSystem::sprite, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    _startTime = std::chrono::steady_clock::now();
}

inline int NetworkServerSystem::getClient(int id)
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

inline int NetworkServerSystem::hourIntNow()
{
    auto currentTime = std::chrono::high_resolution_clock::now();
    auto timeSinceEpoch = currentTime.time_since_epoch();
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(timeSinceEpoch);
    int currentTime_ms = static_cast<int>(milliseconds.count());

    return currentTime_ms;
}

inline std::vector<std::vector<int>> NetworkServerSystem::splitVector(const std::vector<int> &originalVector, size_t maxSize)
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

inline std::vector<int> NetworkServerSystem::mergeVectors(const std::vector<int>& vec1, const std::vector<int>& vec2)
{
    std::vector<int> mergedVector = vec1;

    mergedVector.insert(mergedVector.end(), vec2.begin(), vec2.end());
    return mergedVector;
}

inline std::vector<int> NetworkServerSystem::stringToVector(const std::string& str) {
    std::vector<int> result;

    for (char c : str) {
        result.push_back(static_cast<int>(c));
    }
    return result;
}

inline std::string NetworkServerSystem::vectorToString(const std::vector<int>& data)
{
    std::stringstream ss;

    for (int num : data) {
        ss << static_cast<char>(num); // Conversion des entiers en caractères
    }

    std::string myString = ss.str();

    return myString;
}

inline unsigned short NetworkServerSystem::findValidPort(asio::io_context& service)
{
    asio::ip::udp::socket socket(service);

    for (unsigned short port = 1024; port < 65535; ++port) {
        try {

            asio::ip::udp::endpoint endpoint(asio::ip::udp::v4(), port);

            socket.open(endpoint.protocol());
            socket.bind(endpoint);  
            socket.close();
            return port;
        } catch (std::exception&) {
            socket.close();
        }
    }

    throw std::runtime_error("Could not find an available port.");
}

inline std::vector<unsigned char> NetworkServerSystem::encode(const std::vector<int>& values)
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

inline std::vector<int> NetworkServerSystem::decode(const std::vector<unsigned char>& encodedData, size_t numBytesToRead)
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

inline void NetworkServerSystem::sendCreateRoom(int port, int nbPlayer, std::string name)
{
    std::vector<int> data = {port, nbPlayer};
    int index = 0;

    data = mergeVectors(data, stringToVector(name));
    for (auto client : _clients) {
        send({CREATE_ROOM_CMD, 3}, data, true, client.getClientEndpoint(), index);
        index++;
    }
}

inline void NetworkServerSystem::sprite(std::vector<int>& decodedIntegers, udp::endpoint& clientEndpoint, Coordinator &coordinator)
{
    (void)coordinator;

    int timeStamp = decodedIntegers.at(0);
    int index = getClient(decodedIntegers.at(1));

    if (index == -1)
        return;
    decodedIntegers.erase(decodedIntegers.begin(), decodedIntegers.begin() + 2);

    int size = decodedIntegers.at(0);

    decodedIntegers.erase(decodedIntegers.begin(), decodedIntegers.begin() + 1);
    send({_OK}, {timeStamp}, false, clientEndpoint, index);

    std::vector<int> base64 = {};
    std::vector<int> name = {};

    int y = 0;
    for (auto i : decodedIntegers) {
        if (y == size)
            break;
        base64.push_back(i);
        y++;
    }
    for (size_t i = base64.size(); i < decodedIntegers.size(); ++i)
        name.push_back(decodedIntegers[i]);
    int copy = 0;
    std::string filePath = "./assets/sprite/" + vectorToString(name);
    if (std::filesystem::exists(filePath) == true) {
        while (1) {
            if (std::filesystem::exists("./assets/sprite/" +  std::to_string(copy) + vectorToString(name)) == false)
                break;
            copy++;
        }
        filePath = "./assets/sprite/" +  std::to_string(copy) + vectorToString(name);
    }
    std::ofstream fichier;

    fichier.open(filePath, std::ios::app);
    if (fichier.is_open()) {
        fichier << vectorToString(base64);
        fichier.close();
    } else {
        std::cerr << "Impossible d'ouvrir le fichier." << std::endl;
    }
    int id = _sprite.size();
    int i = 0;
    base64 = mergeVectors(base64, stringToVector(filePath));
    _sprite[id] = std::make_tuple(vectorToString(base64), filePath);
    for (auto client : _clients) {
        send({SPRITE, 3}, mergeVectors({id, size}, base64), true, client.getClientEndpoint(), i);
        i++;
    }
    std::vector<int> data = mergeVectors({id, size}, base64);
    std::vector<int> res = mergeVectors({SPRITE, 3}, data);
    std::vector<unsigned char> buffer = encode(res);
    for (auto room : _room)
        _socket.send_to(asio::buffer(buffer), asio::ip::udp::endpoint(asio::ip::make_address("127.0.0.1"), std::get<0>(room)));
}

inline void NetworkServerSystem::response(std::vector<int>& decodedIntegers, udp::endpoint& clientEndpoint, Coordinator &coordinator)
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

inline void NetworkServerSystem::param(std::vector<int>& decodedIntegers, udp::endpoint& clientEndpoint, Coordinator &coordinator)
{
    (void)clientEndpoint;
    (void)coordinator;

    int timeStamp = decodedIntegers.at(0);
    int index = getClient(decodedIntegers.at(1));
    std::vector<int> selectSprites;

    if (index == -1)
        return;

    int nbPlayer = decodedIntegers.at(2);
    for (std::size_t i = 3; i < 9; i++)
        selectSprites.push_back(decodedIntegers.at(i));
    // int selectBullet = decodedIntegers.at(3);
    // int selectEnnemy = decodedIntegers.at(4);
    // int selectEnnemyTwo = decodedIntegers.at(5);
    // int selectEnnemyElite = decodedIntegers.at(6);
    // int selectEnnemyBoss = decodedIntegers.at(7);
    // int selectEnnemyBullet = decodedIntegers.at(8);

    decodedIntegers.erase(decodedIntegers.begin(), decodedIntegers.begin() + 9);

    std::string name = vectorToString(decodedIntegers);
    int port = findValidPort(_service);

    try {
        std::thread Thread(room, nbPlayer, port, clientEndpoint, _clients.at(index).getUsername(), _sprite, selectSprites);

        Thread.detach();
        send({_OK}, {timeStamp}, false, clientEndpoint, index);
        sendCreateRoom(port, nbPlayer, name);
        _room.push_back(std::make_tuple(port, nbPlayer, name));
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        send({_CREATE_ROOM}, {timeStamp}, false, clientEndpoint, index);
    }
    return;
}

inline void NetworkServerSystem::connect(std::vector<int>& decodedIntegers, udp::endpoint& clientEndpoint, Coordinator &coordinator)
{
    (void)coordinator;

    std::string username = vectorToString(decodedIntegers);

    for (auto client : _clients) {
        if (client.getUsername() == username) {
            // std::vector<unsigned char> buffer = encode(_FAIL_CONNECT);
            // _socket.send_to(asio::buffer(buffer), clientEndpoint);
            return;
        }
    }
    _clients.push_back(Client(username, clientEndpoint, _id, -1));
    _id++;

    std::vector<int> tmp = {_clients.at(_clients.size() - 1).getID()};
    std::vector<unsigned char> buffer = encode(tmp);
    int index = getClient(_id - 1);

    _socket.send_to(asio::buffer(buffer), clientEndpoint);
    tmp = {};
    for (auto room : _room) {
        std::vector<int> data = {std::get<0>(room), std::get<1>(room)};

        data = mergeVectors(data, stringToVector(std::get<2>(room)));
        send({CREATE_ROOM_CMD, 3}, data, true, clientEndpoint, index);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    for (auto sprite : _sprite) {
        std::cout << "send _sprite[" << sprite.first << "]: " << std::get<1>(sprite.second) << std::endl;
        std::vector<int> base64 = stringToVector(std::get<0>(sprite.second));
        int size = base64.size();

        base64 = mergeVectors(base64, stringToVector(std::get<1>(sprite.second)));
        send({SPRITE, 3}, mergeVectors({sprite.first, size}, base64), true, clientEndpoint, index);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

inline void NetworkServerSystem::ping(Coordinator &coordinator)
{
    (void)coordinator;
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

inline void NetworkServerSystem::pong(std::vector<int>& decodedIntegers, udp::endpoint& clientEndpoint, Coordinator &coordinator)
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

inline int NetworkServerSystem::checkAlreadyReceive(std::vector<int>& decodedIntegers, udp::endpoint clientEndpoint)
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
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 0;
    }
}

inline void NetworkServerSystem::handleCmd(std::vector<int>& decodedIntegers, udp::endpoint clientEndpoint, Coordinator &coordinator)
{
    int index = decodedIntegers.at(0);

    if (index < 0 || index > 16)
        return;
    if (decodedIntegers.at(0) == 1) {
        decodedIntegers.erase(decodedIntegers.begin(), decodedIntegers.begin() + 3);
        _functions[index](decodedIntegers, clientEndpoint, coordinator);
        return;
    }
    if (decodedIntegers.size() < 4)
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

inline void NetworkServerSystem::processReceiveData(udp::endpoint clientEndpoint, Coordinator &coordinator, std::vector<int> res)
{
    if (clientEndpoint != asio::ip::udp::endpoint(asio::ip::make_address("0.0.0.0"), 0)) {
        handleCmd(res, clientEndpoint, coordinator);
    } else {
        return;
    }
}

inline void NetworkServerSystem::send(std::vector<int> header, std::vector<int> data, bool stock, udp::endpoint client, int index)
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
        std::cout << " NB PACKETS: " << data.size() << std::endl;

        for (size_t i = 0; i < data.size(); i++) {
            std::cout << "first value: " << data.at(i).at(0) << std::endl;
            buffer = encode(data.at(i));
            _socket.send_to(asio::buffer(buffer), client);
        }
    } else {
        std::cout << "UNIQUE PACKET" << std::endl;
        std::vector<unsigned char> buffer = encode(res);

        _socket.send_to(asio::buffer(buffer), client);
        if (stock == true) {
            _clients.at(index).addPacketSend(timeStamp, buffer);
        }
        buffer.clear();
    }
    std::cout << "SEND END" << std::endl;
    return;
}

inline std::tuple<std::vector<int>, udp::endpoint> NetworkServerSystem::receive()
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

inline void NetworkServerSystem::packetLoss()
{
    for (auto client : _clients) {

        auto packet = client.getPacketsSend();

        for (auto pair : packet) {
            _socket.send_to(asio::buffer(pair.second), client.getClientEndpoint());
        }
    }
}

inline void NetworkServerSystem::Update(Coordinator &coordinator)
{
    std::chrono::seconds interval(5);
    std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
    std::chrono::steady_clock::duration elapsedTime = currentTime - _startTime;

    if (elapsedTime >= interval) {
        packetLoss();
    }
    while (1) {
        try {
            std::vector<int> decodedIntegers;
            udp::endpoint clientEndpoint;
            std::tie(decodedIntegers, clientEndpoint) = receive();

            processReceiveData(clientEndpoint, coordinator, decodedIntegers);
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        } catch (std::exception& e) {
            // std::cerr << "Error: " << e.what() << std::endl;
            break;
        }
    }
    if (elapsedTime >= interval) {
        ping(coordinator);
        _startTime = currentTime;
    }
}