/*
** EPITECH PROJECT, 2023
** RType [WSL: Fedora]
** File description:
** NetworkRoomSystem
*/

#ifndef NETWORKROOMSYSTEM_HPP_
#define NETWORKROOMSYSTEM_HPP_

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
#include "System.hpp"
#include "Coordinator.hpp"
#include "components/Position.hpp"
#include "components/Velocity.hpp"
#include "components/Hitbox.hpp"
#include "EnumProtocol.hpp"
#include "Client.hpp"

class NetworkRoomSystem : public System {
public:

    /**
     * @brief Retrieves the client with the given ID.
     * @param id The ID of the client to retrieve.
     * @return The ID of the client if found, otherwise returns -1.
     */
    int getClient(int id);

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
    void processReceiveData(const std::vector<unsigned char>& data, udp::endpoint clientEndpoint, std::size_t bytesReceived, Coordinator &coordinator);

    /**
     * @brief Converts a vector of integers into a string.
     * @param data The vector of integers to convert.
     * @return A string generated from the vector of integers.
     */
    std::string vectorToString(const std::vector<int>& data);

    /**
     * @brief Finds a valid port to use.
     * @param service The io_service to use for port validation.
     * @return An unsigned short representing the valid port.
     */
    unsigned short findValidPort(asio::io_context& service);

    /**
     * @brief Sends a pong response to a ping request.
     * @param data The vector of integers representing the pong response data.
     * @param clientEndpoint The endpoint of the client requesting pong.
     */
    void pong(std::vector<int>& decodedIntegers, udp::endpoint& clientEndpoint, Coordinator &coordinator);

    /**
     * @brief Establishes a connection with a client.
     * @param data The vector of integers representing connection data.
     * @param clientEndpoint The endpoint of the client attempting to connect.
     */
    void connect(std::vector<int>& decodedIntegers, udp::endpoint& clientEndpoint, Coordinator &coordinator);

    /**
     * @brief Sends a response to a client.
     * @param data The vector of integers for the response data.
     * @param clientEndpoint The endpoint of the client to respond to.
     */
    void response(std::vector<int>& decodedIntegers, udp::endpoint& clientEndpoint, Coordinator &coordinator);

    /**
     * @brief Sends a ping request to all connected clients.
     */
    void ping(Coordinator& coordinator);

    /**
     * @brief Send Ecs to all clients.
     * @param coordinator The Coordinator reference.
     */
    void sendEcs(Coordinator &coordinator);

    /**
     * @brief Handles the received command data.
     * @param data The vector of integers representing the command data.
     * @param clientEndpoint The endpoint of the client sending the command.
     */
    void handleCmd(std::vector<int>& decodedIntegers, udp::endpoint clientEndpoint, Coordinator &coordinator);

    int checkMove(Position& pos, Velocity& vel, Hitbox& hitbox, Entity entity, Coordinator& coordinator);

    void move(std::vector<int>& decodedIntegers, udp::endpoint& clientEndpoint, Coordinator &coordinator);

    void sendDestroy(int entity);

    void sendCreate(int entity, Coordinator &coordinator);

    void Init(int port);

    void Update(Coordinator& coordinator);

protected:
private:
    io_context _service; /**< The Boost ASIO io_service. */
    udp::socket _socket = udp::socket(_service, udp::endpoint(udp::v6(), 0)); /**< The UDP socket for communication. */
    std::vector<Client> _clients; /**< Vector storing information about connected clients. */
    udp::endpoint _serverEndpoint; /**< The endpoint of the server. */
    std::function<void(std::vector<int>&, udp::endpoint&, Coordinator &coordinator)> _functions[14]; /**< Array of function pointers. */
};

#endif /* !NETWORKROOMSYSTEM_HPP_ */
