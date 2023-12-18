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
    _functions[0] = std::bind(&NetworkServerSystem::response, this, std::placeholders::_1, std::placeholders::_2);
    _functions[1] = std::bind(&NetworkServerSystem::connect, this, std::placeholders::_1, std::placeholders::_2);
    _functions[2] = nullptr;
    _functions[3] = nullptr;
    _functions[4] = nullptr;
    _functions[5] = nullptr;
    _functions[6] = std::bind(&NetworkServerSystem::pong, this, std::placeholders::_1, std::placeholders::_2);
    _functions[7] = nullptr;
    _startTime = std::chrono::steady_clock::now();
}

int NetworkServerSystem::getClient(int id)
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

void NetworkServerSystem::response(std::vector<int>& data, udp::endpoint& clientEndpoint)
{
    return;
}

void NetworkServerSystem::connect(std::vector<int>& data, udp::endpoint& clientEndpoint)
{
    std::string username = vectorToString(data);

    std::cout << "username: " << username << std::endl;

    for (auto client : _clients) {
        if (client.getUsername() == username) {
            std::vector<unsigned char> buffer = encode(_FAIL_CONNECT);
            _socket.send_to(asio::buffer(buffer), clientEndpoint);
            return;
        }
    }
    _clients.push_back(Client(username, clientEndpoint, _id));
    _id++;
    std::cout << _clients.at(_clients.size() - 1).getClientEndpoint() << std::endl;
    std::vector<int> tmp = {_clients.at(_clients.size() - 1).getID()};
    std::vector<unsigned char> buffer = encode(tmp);
    _socket.send_to(asio::buffer(buffer), clientEndpoint);
}

void NetworkServerSystem::ping()
{
    _clients.erase(
        std::remove_if(
            _clients.begin(),
            _clients.end(),
            [](Client& client) {
                if (!client.getAlive()) {
                    std::cout << "DELETE CLIENT ID: " << client.getID() << std::endl;
                    return true; // Supprime les clients dont getAlive() retourne false
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
        _socket.send_to(asio::buffer(buffer), client.getClientEndpoint());
    }
}

void NetworkServerSystem::pong(std::vector<int>& data, udp::endpoint& clientEndpoint)
{
    std::cout << "RECEIVE PONG" << std::endl;
    std::cout << "CLIENT ID ALIVE: " << data.at(0) << std::endl;
    int index = getClient(data.at(0));

    if (index == -1) {
        return;
    }
    std::cout << "CLIENT ID ALIVE: " << data.at(0) << std::endl;
    std::vector<unsigned char> buffer = encode(_PASS);
    _socket.send_to(asio::buffer(buffer), _clients.at(index).getClientEndpoint());
    _clients.at(index).setAlive(true);
}

void NetworkServerSystem::handleCmd(std::vector<int> data, udp::endpoint clientEndpoint)
{
    int index = data.at(0);

    if (_functions[index] != nullptr) {
        data.erase(data.begin(), data.begin() + 2);
        _functions[index](data, clientEndpoint);
    }
    else {
        std::vector<unsigned char> buffer = encode(_UNKNOW);
        _socket.send_to(asio::buffer(buffer), clientEndpoint);
    }
}

void NetworkServerSystem::processReceiveData(const std::vector<unsigned char>& data, udp::endpoint clientEndpoint, std::size_t bytesReceived)
{
    if (clientEndpoint != asio::ip::udp::endpoint(asio::ip::make_address("0.0.0.0"), 0)) {
        std::vector<int> res = decode(data, bytesReceived);
        for (auto i : res)
            std::cout << i << std::endl;
        handleCmd(res, clientEndpoint);
    } else {
        return;
    }
}

void NetworkServerSystem::Update(Coordinator &coordinator)
{
    std::chrono::seconds interval(5);
    std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
    std::chrono::steady_clock::duration elapsedTime = currentTime - _startTime;
    std::vector<unsigned char> data(1024);
    udp::endpoint clientEndpoint;

    try {
        size_t length = _socket.receive_from(asio::buffer(data), clientEndpoint, 0);
        processReceiveData(data, clientEndpoint, length);
    } catch (const std::system_error& e) {

    }
    if (elapsedTime >= interval) {
        std::cout << "PING PACKET" << std::endl;
        ping();
        _startTime = currentTime;
    }
}