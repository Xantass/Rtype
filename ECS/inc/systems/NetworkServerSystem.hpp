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
#include <asio.hpp>
#include <sstream>
#include "System.hpp"
#include "Coordinator.hpp"
#include "components/Position.hpp"
#include "components/Velocity.hpp"
#include "EnumProtocol.hpp"
#include "Client.hpp"

using namespace asio;
using asio::ip::udp;

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
    void processReceiveData(const std::vector<unsigned char>& data, udp::endpoint clientEndpoint, std::size_t bytesReceived);

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

    /**
     * @brief Handles the received command data.
     * @param data The vector of integers representing the command data.
     * @param clientEndpoint The endpoint of the client sending the command.
     */
    void handleCmd(std::vector<int> data, udp::endpoint clientEndpoint);

    /**
     * @brief Sends a response to a client.
     * @param data The vector of integers for the response data.
     * @param clientEndpoint The endpoint of the client to respond to.
     */
    void response(std::vector<int>& data, udp::endpoint& clientEndpoint);

    /**
     * @brief Establishes a connection with a client.
     * @param data The vector of integers representing connection data.
     * @param clientEndpoint The endpoint of the client attempting to connect.
     */
    void connect(std::vector<int>& data, udp::endpoint& clientEndpoint);

    /**
     * @brief Sends a pong response to a ping request.
     * @param data The vector of integers representing the pong response data.
     * @param clientEndpoint The endpoint of the client requesting pong.
     */
    void pong(std::vector<int>& data, udp::endpoint& clientEndpoint);

    /**
     * @brief Sends a ping request to all connected clients.
     */
    void ping();

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
    std::function<void(std::vector<int>&, udp::endpoint&)> _functions[8]; /**< Array of function pointers. */
    std::chrono::steady_clock::time_point _startTime; /**< The start time for tracking. */
    int _id = 0; /**< The ID of the server. */
};

#endif /* !NETWORKSERVERSYSTEM_HPP_ */