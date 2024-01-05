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
    Client(std::string username, udp::endpoint clientEndpoint, int id);

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

    std::map<int, std::vector<unsigned char>> getPacketsSend() const;

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

    void addPacketSend(int timeStamp, std::vector<unsigned char> packet);

    void delPacketSend(int timeStamp);

    void addPacketReceive(int timeStamp, std::vector<int> packet);

    void delPacketReceive(int timeStamp);

protected:
private:
    std::string _username; /**< The username of the client. */
    int _ID; /**< The ID of the client. */
    udp::endpoint _clientEndpoint; /**< The UDP endpoint of the client. */
    bool _alive; /**< The status of the client (alive or not). */
    std::map<int, std::vector<unsigned char>> _packetsSend;
    std::map<int, std::vector<int>> _packetsReceive;
};

#endif /* !CLIENT_HPP_ */
