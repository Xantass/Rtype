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

#if defined(_WIN32)           
	#define NOGDI             // All GDI defines and routines
	#define NOUSER            // All USER defines and routines
#endif

#include <asio.hpp> // or any library that uses Windows.h

#if defined(_WIN32)           // raylib uses these names as function parameters
	#undef near
	#undef far
#endif
#include "System.hpp"
#include "Coordinator.hpp"
#include "components/Position.hpp"
#include "components/Velocity.hpp"
#include "components/Hitbox.hpp"
#include "components/Sprite.hpp"
#include "EnumProtocol.hpp"

using namespace asio;
using asio::ip::udp;

/**
 * @class NetworkClientSystem
 * @brief Handles network communication on the client side.
 */
class NetworkClientSystem : public System {
public:
    /**
     * @brief Initializes the NetworkClientSystem.
     * @param coordinator The Coordinator reference.
     */
    void Init(Coordinator &coordinator);

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
     * @param decodedIntegers The vector of integers representing the command data.
     */
    void handleCmd(std::vector<int>& decodedIntegers, Coordinator &coordinator);

    /**
     * @brief Sends a ping request.
     * @param decodedIntegers The vector of integers for ping request data.
     */
    void ping(std::vector<int>& decodedIntegers, Coordinator &coordinator);

    /**
     * @brief Sends position data.
     * @param decodedIntegers The vector of integers for position data.
     */
    void pos(std::vector<int>& decodedIntegers, Coordinator &coordinator);

    /**
     * @brief Creates entities based on decoded data.
     * @param decodedIntegers The vector of integers representing entity data.
     * @param coordinator The Coordinator reference.
     */
    void createEntities(std::vector<int> decodedIntegers, Coordinator &coordinator);

    void checkEvent(Coordinator &coordinator);

    /**
     * @brief Updates the NetworkClientSystem.
     * @param coordinator The Coordinator reference.
     */
    void Update(Coordinator &coordinator);

protected:
private:
    io_context _service; /**< The Boost ASIO io_service. */
    udp::socket _socket = udp::socket(_service, udp::endpoint(udp::v4(), findValidPort(_service))); /**< The UDP socket for communication. */
    udp::endpoint _serverEndpoint; /**< The endpoint of the server. */
    std::function<void(std::vector<int>&, Coordinator &coordinator)> _functions[8]; /**< Array of function pointers. */
    int _id; /**< The ID of the client. */
};

#endif /* NETWORKCLIENTSYSTEM_HPP_ */