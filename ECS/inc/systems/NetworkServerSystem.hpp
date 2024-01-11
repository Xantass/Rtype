/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** NetworkServerSystem
*/

/**
 * @file NetworkServerSystem.hpp
 * @brief Header file defining the NetworkServerSystem class.
 */

#ifndef NETWORKSERVERSYSTEM_HPP_
#define NETWORKSERVERSYSTEM_HPP_

#include <functional>
#include <chrono>
#if defined(_WIN32)           
	#define NOGDI             // All GDI defines and routines
	#define NOUSER            // All USER defines and routines
#endif

#include <asio.hpp> // or any library that uses Windows.h

#if defined(_WIN32)           // raylib uses these names as function parameters
	#undef near
	#undef far
#endif
#include <sstream>
#include <thread>
#include "EnumProtocol.hpp"
#include "../../server/inc/Client.hpp"
#include "System.hpp"
#include "components/Position.hpp"
#include "components/Velocity.hpp"
#include "components/Hitbox.hpp"
#include "components/Movable.hpp"
#include "components/Controllable.hpp"
#include "components/HealthPoint.hpp"
#include "components/Damage.hpp"


using namespace asio;
using asio::ip::udp;

int room(int nbPlayer, int port, udp::endpoint clientEndpoint, std::string nameAdmin);

/**
 * @class NetworkServerSystem
 * @brief Handles server-side network communication.
 */
class NetworkServerSystem : public System {
public:
    /**
     * @brief Initializes the NetworkServerSystem.
     */
    void Init();

    /**
     * @brief Retrieves the client with the given ID.
     * @param id The ID of the client to retrieve.
     * @return The ID of the client if found, otherwise returns -1.
     */
    int getClient(int id);

    /**
     * @brief Obtains the current hour as an integer.
     * @return An integer representing the current hour.
     */
    int hourIntNow();

    /**
     * @brief Finds a valid port to use.
     * @param service The io_service to use for port validation.
     * @return An unsigned short representing the valid port.
     */
    unsigned short findValidPort(asio::io_context& service);

    /**
     * @brief Encodes a vector of integers into a vector of bytes.
     * @param values The vector of integers to encode.
     * @return A vector of bytes representing the encoded data.
     */
    std::vector<unsigned char> encode(const std::vector<int>& values);

    /**
     * @brief Decodes a vector of bytes into a vector of integers.
     * @param encodedData The vector of bytes to decode.
     * @param numBytesToRead The number of bytes to read for decoding.
     * @return A vector of integers representing the decoded data.
     */
    std::vector<int> decode(const std::vector<unsigned char>& encodedData, size_t numBytesToRead);

    /**
     * @brief Processes received data.
     * @param data The received data in vector format.
     * @param clientEndpoint The endpoint of the client.
     * @param bytesReceived The number of bytes received.
     */
    void processReceiveData(udp::endpoint clientEndpoint, Coordinator &coordinator, std::vector<int> res);

    /**
     * @brief Merges two vectors of integers into a single vector.
     * @param vec1 The first vector of integers.
     * @param vec2 The second vector of integers.
     * @return A merged vector of integers.
     */
    std::vector<int> mergeVectors(const std::vector<int>& vec1, const std::vector<int>& vec2);

    /**
     * @brief Converts a string into a vector of integers.
     * @param str The string to convert.
     * @return A vector of integers generated from the string.
     */
    std::vector<int> stringToVector(const std::string& str);

    /**
     * @brief Converts a vector of integers into a string.
     * @param data The vector of integers to convert.
     * @return A string generated from the vector of integers.
     */
    std::string vectorToString(const std::vector<int>& data);

    void sendCreateRoom(int port, int nbPlayer, std::string name);

    /**
     * @brief Handles the received command data.
     * @param data The vector of integers representing the command data.
     * @param clientEndpoint The endpoint of the client sending the command.
     */
    void handleCmd(std::vector<int>& decodedIntegers, udp::endpoint clientEndpoint, Coordinator &coordinator);

    /**
     * @brief Sends a response to a client.
     * @param data The vector of integers for the response data.
     * @param clientEndpoint The endpoint of the client to respond to.
     */
    void response(std::vector<int>& decodedIntegers, udp::endpoint& clientEndpoint, Coordinator &coordinator);

    /**
     * @brief Establishes a connection with a client.
     * @param data The vector of integers representing connection data.
     * @param clientEndpoint The endpoint of the client attempting to connect.
     */
    void connect(std::vector<int>& decodedIntegers, udp::endpoint& clientEndpoint, Coordinator &coordinator);

    /**
     * @brief Sends a pong response to a ping request.
     * @param data The vector of integers representing the pong response data.
     * @param clientEndpoint The endpoint of the client requesting pong.
     */
    void pong(std::vector<int>& decodedIntegers, udp::endpoint& clientEndpoint, Coordinator &coordinator);

    /**
     * @brief Sends a ping request to all connected clients.
     */
    void ping(Coordinator& coordinator);

    /**
     * @brief Handles parameter data received from a client.
     * @param decodedIntegers The vector of integers representing the parameter data.
     * @param clientEndpoint The endpoint of the client sending the parameter data.
     * @param coordinator The Coordinator reference.
     */

    void param(std::vector<int>& decodedIntegers, udp::endpoint& clientEndpoint, Coordinator &coordinator);

    /**
     * @brief Sends a packet with header and data to a specific client endpoint, optionally storing it.
     * @param header The header data for the packet.
     * @param data The actual data payload for the packet.
     * @param stock Boolean indicating whether to store the packet.
     * @param clientEndpoint The endpoint of the client to send the packet to.
     * @param index The index for packet identification.
     */
    void send(std::vector<int> header, std::vector<int> data, bool stock, udp::endpoint clientEndpoint, int index);

    /**
     * @brief Checks if a packet with the given header has already been received from a specific client endpoint.
     * @param decodedIntegers The decoded integers representing the packet header.
     * @param clientEndpoint The endpoint of the client to check for packet reception.
     * @return An integer indicating the packet's reception status.
     */
    int checkAlreadyReceive(std::vector<int>& decodedIntegers, udp::endpoint clientEndpoint);

    /**
     * @brief Handles packet loss and manages related actions.
     */
    void packetLoss();

    /**
     * @brief Receives a packet along with its endpoint information.
     * @return A tuple containing the vector of integers representing the received packet
     *         and the endpoint from which the packet was received.
     */
    std::tuple<std::vector<int>, udp::endpoint> receive();

    /**
     * @brief Sends an ECS (Entity-Component-System) update to the Coordinator.
     * @param coordinator The Coordinator reference for ECS update.
     */
    void sendEcs(Coordinator &coordinator);

    /**
     * @brief Updates the NetworkServerSystem.
     * @param coordinator The Coordinator reference.
     */
    void Update(Coordinator &coordinator);

protected:
private:
    io_context _service; /**< The Boost ASIO io_service. */
    udp::socket _socket = udp::socket(_service, udp::endpoint(udp::v4(), 4242)); /**< The UDP socket for communication. */
    std::vector<Client> _clients; /**< Vector storing information about connected clients. */
    std::function<void(std::vector<int>&, udp::endpoint&, Coordinator &coordinator)> _functions[16]; /**< Array of function pointers. */
    std::chrono::steady_clock::time_point _startTime; /**< The start time for tracking. */
    int _id = 0; /**< The ID of the server. */
    int _port = 4243;
    std::vector<std::tuple<int, int, std::string>> _room;
};

#include "../../src/systems/NetworkServerSystem.cpp"

#endif /* !NETWORKSERVERSYSTEM_HPP_ */
