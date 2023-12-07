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
#else
    #include <arpa/inet.h>
    #include <sys/socket.h>
#endif

#include <iostream>
#include <vector>
#include <cstdlib>
#include <csignal>
#include <cstring>
#include <unistd.h>
#include <sys/select.h>
#include <memory>

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

protected:
private:
    int _serverSocket; /**< The server's socket file descriptor */
    int _port; /**< The port number the server is listening on */
    int _maxSocket; /**< The maximum number of sockets */
    sockaddr_in _serverAddr{}; /**< Server address information */
    std::vector<int> _clientSockets; /**< Vector to store client sockets */
    fd_set _readfds; /**< File descriptor set for select() */
};

#endif /* !SERVER_HPP_ */
