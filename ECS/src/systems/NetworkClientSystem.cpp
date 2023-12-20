/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** NetworkClientSystem
*/

#include "NetworkClientSystem.hpp"

#define CHECK_ZERO(x) x == 0 ? static_cast<float>(x) : static_cast<float>(x) / 10
#define CHECK_TYPE(x) x == 0 ? PLAYER : ENNEMY

void NetworkClientSystem::Init(Coordinator &coordinator)
{
    udp::resolver resolver(_service);
    _serverEndpoint = *resolver.resolve(udp::v4(), "192.168.1.189", "4242").begin();
    std::vector<int> tmp = mergeVectors(_CONNECT, stringToVector("THEO"));
    std::vector<unsigned char> buffer = encode(tmp);
    _socket.send_to(asio::buffer(buffer), _serverEndpoint);
    std::vector<unsigned char> data(1024);
    //CREATE ENTITY AFTER RECEIVE FROM
    size_t length = _socket.receive_from(asio::buffer(data), _serverEndpoint, 0);
    std::vector<int> decodedIntegers = decode(data, length);
    _id = decodedIntegers.at(0);
    std::cout << "id: " << _id << std::endl;
    Entity entity = coordinator.CreateEntity(this->_id);
    coordinator.AddComponent<Position>(entity, {1, 0});
    coordinator.AddComponent<Velocity>(entity, {0, 0});
    coordinator.AddComponent<Hitbox>(entity, {0, 0, 1, 1, PLAYER});
    length = _socket.receive_from(asio::buffer(data), _serverEndpoint, 0);
    decodedIntegers = decode(data, length);
    createEntities(decodedIntegers, coordinator);
    _functions[0] = nullptr;
    _functions[1] = nullptr;
    _functions[2] = nullptr;
    _functions[3] = nullptr;
    _functions[4] = std::bind(&NetworkClientSystem::pos, this, std::placeholders::_1);
    _functions[5] = std::bind(&NetworkClientSystem::ping, this, std::placeholders::_1);
    _functions[6] = nullptr;
    _functions[7] = nullptr;
    _socket.non_blocking(true);
}

void NetworkClientSystem::createEntities(std::vector<int> decodedInteger, Coordinator &coordinator)
{
    std::cout << "CREATE" << std::endl;
    decodedInteger.erase(decodedInteger.begin(), decodedInteger.begin() + 1);
    std::cout << "SIZE: " << decodedInteger.size() << std::endl;
    while (decodedInteger.empty() == false) {
        //ADD INT FOR ID ENTITY
        Entity entity = coordinator.CreateEntity();
        coordinator.AddComponent<Position>(entity, {CHECK_ZERO(decodedInteger.at(1)), CHECK_ZERO(decodedInteger.at(2))});
        coordinator.AddComponent<Velocity>(entity, {CHECK_ZERO(decodedInteger.at(3)), CHECK_ZERO(decodedInteger.at(4))});
        coordinator.AddComponent<Hitbox>(entity, {CHECK_ZERO(decodedInteger.at(5)), CHECK_ZERO(decodedInteger.at(6)), CHECK_ZERO(decodedInteger.at(7)), CHECK_ZERO(decodedInteger.at(8)), CHECK_TYPE(decodedInteger.at(9))});
        decodedInteger.erase(decodedInteger.begin(), decodedInteger.begin() + 10);
    }
}

unsigned short NetworkClientSystem::findValidPort(asio::io_context& service)
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

void NetworkClientSystem::ping(std::vector<int>& decodedIntegers)
{
    std::vector<int> tmp = {_id};
    std::vector<unsigned char> buffer = encode(mergeVectors(_PONG, tmp));
    _socket.send_to(asio::buffer(buffer), _serverEndpoint);  
}

void NetworkClientSystem::pos(std::vector<int>& decodedIntegers)
{
    
}

void NetworkClientSystem::handleCmd(std::vector<int>& decodedIntegers)
{
    int index = decodedIntegers.at(0);

    for (auto i : decodedIntegers)
        std::cout << i << std::endl;
    if (_functions[index] != nullptr) {
        decodedIntegers.erase(decodedIntegers.begin(), decodedIntegers.begin() + 2);
        _functions[index](decodedIntegers);
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

void NetworkClientSystem::Update(Coordinator &coordinator)
{
    std::vector<unsigned char> data(1024);
    udp::endpoint receiveEndpoint;

    try {
        size_t length = _socket.receive_from(asio::buffer(data), receiveEndpoint, 0);
        std::vector<int> decodedIntegers = decode(data, length);
        handleCmd(decodedIntegers);
    } catch (const std::system_error& e) {

    }
}