/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** NetworkClientSystem
*/

#include "NetworkClientSystem.hpp"

void NetworkClientSystem::Init()
{
    udp::resolver resolver(_service);
    _serverEndpoint = *resolver.resolve(udp::v4(), "172.20.10.4", "4242").begin();
    std::vector<int> tmp = mergeVectors(_CONNECT, stringToVector("THEO"));
    std::vector<unsigned char> buffer = encode(tmp);
    _socket.send_to(asio::buffer(buffer), _serverEndpoint);
    std::vector<unsigned char> data(1024);
    size_t length = _socket.receive_from(asio::buffer(data), _serverEndpoint, 0);
    tmp = decode(data, length);
    _id = tmp.at(0);
    std::cout << "id: " << _id << std::endl;
    _functions[0] = nullptr;
    _functions[1] = nullptr;
    _functions[2] = nullptr;
    _functions[3] = nullptr;
    _functions[4] = nullptr;
    _functions[5] = std::bind(&NetworkClientSystem::ping, this, std::placeholders::_1);
    _functions[6] = nullptr;
    _functions[7] = nullptr;
    _socket.non_blocking(true);
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

void NetworkClientSystem::ping(std::vector<int>& data)
{
    std::vector<int> tmp = {_id};
    std::vector<unsigned char> buffer = encode(mergeVectors(_PONG, tmp));
    _socket.send_to(asio::buffer(buffer), _serverEndpoint);  
}

void NetworkClientSystem::handleCmd(std::vector<int> data)
{
    int index = data.at(0);

    for (auto i : data)
        std::cout << i << std::endl;
    if (_functions[index] != nullptr) {
        data.erase(data.begin(), data.begin() + 2);
        _functions[index](data);
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
        std::vector<int> res = decode(data, length);
        handleCmd(res);
    } catch (const std::system_error& e) {

    }
}