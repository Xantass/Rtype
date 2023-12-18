/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** NetworkClientSystem
*/

/**
 * @file NetworkClientSystem.hpp
 * @brief Header file defining the NetworkClientSystem class.
 */

#ifndef NETWORKCLIENTSYSTEM_HPP_
#define NETWORKCLIENTSYSTEM_HPP_

#include <boost/asio.hpp>
#include "System.hpp"
#include "Coordinator.hpp"
#include "components/Position.hpp"
#include "components/Velocity.hpp"
#include "EnumProtocol.hpp"

using namespace boost::asio;
using boost::asio::ip::udp;

/**
 * @class NetworkClientSystem
 * @brief Handles network communication on the client side.
 */
class NetworkClientSystem : public System {
public:
    /**
     * @brief Initializes the NetworkClientSystem.
     */
    void Init();

    /**
     * @brief Finds a valid port to use.
     * @param service The io_service to use for port validation.
     * @return An unsigned short representing the valid port.
     */
    unsigned short findValidPort(boost::asio::io_service& service);

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
     * @brief Handles the received command data.
     * @param data The vector of integers representing the command data.
     */
    void handleCmd(std::vector<int> data);

    /**
     * @brief Sends a ping request.
     * @param data The vector of integers for ping request data.
     */
    void ping(std::vector<int>& data);

    /**
     * @brief Updates the NetworkClientSystem.
     * @param coordinator The Coordinator reference.
     */
    void Update(Coordinator &coordinator);

protected:
private:
    io_service _service; /**< The Boost ASIO io_service. */
    udp::socket _socket = udp::socket(_service, udp::endpoint(udp::v4(), findValidPort(_service))); /**< The UDP socket for communication. */
    udp::endpoint _serverEndpoint; /**< The endpoint of the server. */
    std::function<void(std::vector<int>&)> _functions[8]; /**< Array of function pointers. */
    int _id; /**< The ID of the client. */
};

#endif /* NETWORKCLIENTSYSTEM_HPP_ */