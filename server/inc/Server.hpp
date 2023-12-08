/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** Server
*/

/**
 * @file Server.hpp
 * @brief This is the file for the Server class
 * @details The contained class in this file is to be deleted when the project is started
 * 
 */

#ifndef SERVER_HPP_
#define SERVER_HPP_

#ifdef _WIN32 // Vérifie si le système d'exploitation est Windows
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #define NOMINMAX // Pour éviter les conflits de noms
    #include <windows.h>
    #include <winsock2.h>
    #define FD_SETSIZE 64 // Taille arbitraire, adaptez-la à vos besoins
    #define close closesocket
#else
    #include <arpa/inet.h>
    #include <sys/socket.h>
    #include <sys/select.h>
    #include <unistd.h>
#endif

#include <iostream>
#include <vector>
#include <cstdlib>
#include <csignal>
#include <cstring>
#include <memory>
#include <thread>
#include <mutex>
#include <string>
#include <bitset>
#include "RoomManager.hpp"

class Server {
public:
    /**
     * @brief Construct a new Server object
     * 
     * @param port The port number to bind the server to
     */
    Server(size_t port);

    /**
     * @brief Destroy the Server object
     * 
     */
    ~Server();

    /**
     * @brief Starts the server
     * 
     * @return true if the server starts successfully, false otherwise
     */
    bool start();

    /**
     * @brief Closes all client sockets
     * 
     */
    void closeSockets();

    /**
     * @brief Initializes the server socket
     * 
     */
    void initSocket();

    /**
     * @brief Main loop for the server to handle client connections
     * 
     * @return true if the loop runs successfully, false otherwise
     */
    bool loop();

    /**
     * @brief Receives data from a specific client
     * 
     * @param client The client socket to receive data from
     */
    void receiveData(int client);

    /**
     * @brief Checks if a given port is available
     * 
     * @param port The port number to check
     * @return 0 if the port is available, -1 otherwise
     */
    int portAvailable(int port);

    /**
     * @brief Checks the received command from a client
     * 
     * @param buffer The command buffer received from the client
     * @param clientSocket The socket associated with the client
     */
    void checkCmd(std::string buffer, int clientSocket);

    /**
     * @brief Checks and manages threads associated with clients
     * 
     */
    void checkThreads();

    /**
     * @brief Closes all running threads
     * 
     */
    void closeThreads();

    /**
     * @brief Converts a string to binary representation
     * 
     * @param buffer The input string to convert to binary
     * @return The binary representation of the input string
     */
    std::string stringToBinary(const std::string buffer);

    /**
     * @brief Converts a binary string to its string representation
     * 
     * @param buffer The binary string to convert to a regular string
     * @return The string representation of the input binary string
     */
    std::string binaryToString(const std::string buffer);

protected:
private:
    int _serverSocket; /**< The server's socket file descriptor */
    int _port; /**< The port number the server is listening on */
    int _maxSocket; /**< The maximum number of sockets */
    sockaddr_in _serverAddr{}; /**< Server address information */
    std::vector<int> _clientSockets; /**< Vector to store client sockets */
    fd_set _readfds; /**< File descriptor set for select() */
    std::vector<std::thread> _threads; /**< Vector to store threads */
};


#endif /* !SERVER_HPP_ */
