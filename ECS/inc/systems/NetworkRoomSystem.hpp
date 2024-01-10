/*
** EPITECH PROJECT, 2023
** RType [WSL: Fedora]
** File description:
** NetworkRoomSystem
*/

/**
 * @file NetworkRoomSystem.hpp
 * @brief Header file defining the NetworkRoomSystem class.
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
#include "components/Movable.hpp"
#include "components/Controllable.hpp"
#include "EnumProtocol.hpp"
#include "Client.hpp"

/**
 * @class NetworkRoomSystem
 * @brief Handles networking for room-related activities.
 */

class NetworkRoomSystem : public System {
public:
    // Methods

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
     * @brief Merges two vectors of integers into a single vector.
     * @param vec1 The first vector of integers.
     * @param vec2 The second vector of integers.
     * @return A merged vector of integers.
     */
    std::vector<int> mergeVectors(const std::vector<int>& vec1, const std::vector<int>& vec2);

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
     * @param coordinator The Coordinator reference.
     */
    void processReceiveData(udp::endpoint clientEndpoint, Coordinator &coordinator, std::vector<int> res);

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
     * @param decodedIntegers The vector of integers representing the pong response data.
     * @param clientEndpoint The endpoint of the client requesting pong.
     * @param coordinator The Coordinator reference.
     */
    void pong(std::vector<int>& decodedIntegers, udp::endpoint& clientEndpoint, Coordinator &coordinator);

    /**
     * @brief Sends a response to a client.
     * @param decodedIntegers The vector of integers for the response data.
     * @param clientEndpoint The endpoint of the client to respond to.
     * @param coordinator The Coordinator reference.
     */
    void response(std::vector<int>& decodedIntegers, udp::endpoint& clientEndpoint, Coordinator &coordinator);

    /**
     * @brief Establishes a connection with a client.
     * @param decodedIntegers The vector of integers representing connection data.
     * @param clientEndpoint The endpoint of the client attempting to connect.
     * @param coordinator The Coordinator reference.
     */
    void connect(std::vector<int>& decodedIntegers, udp::endpoint& clientEndpoint, Coordinator &coordinator);


    /**
     * @brief Sends a ping request to all connected clients.
     * @param coordinator The Coordinator reference.
     */
    void ping(Coordinator& coordinator);

    /**
     * @brief Send Ecs to all clients.
     * @param coordinator The Coordinator reference.
     */
    void sendEcs(Coordinator &coordinator);

    /**
     * @brief Handles the received command data.
     * @param decodedIntegers The vector of integers representing the command data.
     * @param clientEndpoint The endpoint of the client sending the command.
     * @param coordinator The Coordinator reference.
     */
    void handleCmd(std::vector<int>& decodedIntegers, udp::endpoint clientEndpoint, Coordinator &coordinator);

    /**
     * @brief Checks movement for an entity.
     * @param pos The Position component.
     * @param vel The Velocity component.
     * @param hitbox The Hitbox component.
     * @param entity The entity to check movement for.
     * @param coordinator The Coordinator reference.
     * @return An integer indicating the movement state.
     */
    int checkMove(Position& pos, Velocity& vel, Hitbox& hitbox, Entity entity, Coordinator& coordinator);

    /**
     * @brief Moves an entity.
     * @param decodedIntegers The vector of integers representing movement data.
     * @param clientEndpoint The endpoint of the client requesting movement.
     * @param coordinator The Coordinator reference.
     */
    void move(std::vector<int>& decodedIntegers, udp::endpoint& clientEndpoint, Coordinator &coordinator);

    /**
     * @brief Handles a shooting action initiated by a client.
     * @param decodedIntegers The vector of integers representing the shooting data.
     * @param clientEndpoint The endpoint of the client performing the shooting action.
     * @param coordinator The Coordinator reference.
     */
    void shoot(std::vector<int>& decodedIntegers, udp::endpoint& clientEndpoint, Coordinator &coordinator);


    /**
     * @brief Sends a destroy signal for an entity.
     * @param entity The entity to destroy.
     */
    void sendDestroy(int entity);

    /**
     * @brief Sends a create signal for an entity.
     * @param entity The entity to create.
     * @param coordinator The Coordinator reference.
     */
    void sendCreate(int entity, Coordinator &coordinator);

    /**
     * @brief Initializes the NetworkRoomSystem with a specific port.
     * @param port The port to use for communication.
     */
    void Init(int port);

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
     * @brief checks and run intern server events.
     * @param coordinator The Coordinator reference.
     */
    void checkEvent(Coordinator &coordinator);

    /**
     * @brief Updates the NetworkRoomSystem.
     * @param coordinator The Coordinator reference.
     */
    void Update(Coordinator& coordinator);

protected:
private:
    io_context _service; /**< The Boost ASIO io_service. */
    udp::socket _socket = udp::socket(_service, udp::endpoint(udp::v6(), 0)); /**< The UDP socket for communication. */
    std::vector<Client> _clients; /**< Vector storing information about connected clients. */
    udp::endpoint _serverEndpoint; /**< The endpoint of the server. */
    std::function<void(std::vector<int>&, udp::endpoint&, Coordinator &coordinator)> _functions[14]; /**< Array of function pointers. */
    std::chrono::steady_clock::time_point _startTime; /**< The start time for tracking. */
};

#include "../../src/systems/NetworkRoomSystem.cpp"

#endif /* !NETWORKROOMSYSTEM_HPP_ */
