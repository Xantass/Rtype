/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Client
*/

/**
 * @file Client.hpp
 * @brief Header file defining the Client class.
 */

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#if defined(_WIN32)           
	#define NOGDI             // All GDI defines and routines
	#define NOUSER            // All USER defines and routines
#endif

#include <asio.hpp> // or any library that uses Windows.h

#if defined(_WIN32)           // raylib uses these names as function parameters
	#undef near
	#undef far
#endif

#include <string>
#include <map>
#include <vector>

using namespace asio;
using asio::ip::udp;

/**
 * @class Client
 * @brief Represents a client in the network.
 */
class Client {
public:
    /**
     * @brief Constructor for the Client class.
     * @param username The username of the client.
     * @param clientEndpoint The UDP endpoint of the client.
     * @param id The ID of the client.
     */
    Client(std::string username, udp::endpoint clientEndpoint, int id, int sprite);

    /**
     * @brief Copy constructor for the Client class.
     * @param other The other Client object to copy.
     */
    Client(const Client& other);

    /**
     * @brief Destructor for the Client class.
     */
    ~Client();

    // Getters

    /**
     * @brief Gets the username of the client.
     * @return The username of the client.
     */
    std::string getUsername() const;

    /**
     * @brief Gets the ID of the client.
     * @return The ID of the client.
     */
    int getID() const;

    /**
     * @brief Gets the UDP endpoint of the client.
     * @return The UDP endpoint of the client.
     */
    udp::endpoint getClientEndpoint() const;

    /**
     * @brief Checks if the client is alive.
     * @return True if the client is alive, otherwise false.
     */
    bool getAlive() const;

    /**
     * @brief Gets the map of sent packets.
     * @return A constant reference to the map associating timestamps to vectors of bytes representing sent packets.
     */
    std::map<int, std::vector<unsigned char>> getPacketsSend() const;

    /**
     * @brief Gets the map of received packets.
     * @return A constant reference to the map associating timestamps to vectors of integers representing received packets.
     */
    std::map<int, std::vector<int>> getPacketsReceive() const;

    // Setters

    /**
     * @brief Sets the username of the client.
     * @param username The username to set.
     */
    void setUsername(const std::string& username);

    /**
     * @brief Sets the ID of the client.
     * @param id The ID to set.
     */
    void setID(int id);

    /**
     * @brief Sets the UDP endpoint of the client.
     * @param clientEndpoint The UDP endpoint to set.
     */
    void setClientEndpoint(const udp::endpoint& clientEndpoint);

    /**
     * @brief Sets the status of the client.
     * @param alive The status to set.
     */
    void setAlive(const bool& alive);

    /**
     * @brief Adds a packet to the send queue with the given timestamp.
     * @param timeStamp The timestamp for the packet.
     * @param packet The vector of bytes representing the packet.
     */
    void addPacketSend(int timeStamp, std::vector<unsigned char> packet);

    /**
     * @brief Deletes a packet from the send queue based on the timestamp.
     * @param timeStamp The timestamp of the packet to delete.
     */
    void delPacketSend(int timeStamp);

    /**
     * @brief Adds a packet to the receive queue with the given timestamp.
     * @param timeStamp The timestamp for the packet.
     * @param packet The vector of integers representing the packet.
     */
    void addPacketReceive(int timeStamp, std::vector<int> packet);

    /**
     * @brief Deletes a packet from the receive queue based on the timestamp.
     * @param timeStamp The timestamp of the packet to delete.
     */
    void delPacketReceive(int timeStamp);

    /**
     * @brief Sets the sprite value.
     * @param value The new sprite value to set.
     */
    void setSprite(int value);

    /**
     * @brief Gets the sprite value.
     * @return The current sprite value.
     */
    int getSprite() const;

protected:
private:
    std::string _username; /**< The username of the client. */
    int _ID; /**< The ID of the client. */
    udp::endpoint _clientEndpoint; /**< The UDP endpoint of the client. */
    bool _alive; /**< The status of the client (alive or not). */
    std::map<int, std::vector<unsigned char>> _packetsSend; /**< Map associating timestamps to vectors of bytes representing sent packets. */
    std::map<int, std::vector<int>> _packetsReceive; /**< Map associating timestamps to vectors of integers representing received packets. */
    int _sprite; /**< The sprite value for the network system. */
};

#endif /* !CLIENT_HPP_ */
