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

#include <iostream>
#include <vector>
#include <cstdlib>
#include <csignal>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/select.h>

/**
 * @brief This is the Server class
 * @details This class is to be deleted when the project is started
 * 
 */
class Server {
public:
    /**
     * @brief Construct a new Server object
     * 
     */
    Server(size_t port);

    /**
     * @brief Destroy the Server object
     * 
     */
    ~Server();

    bool start();
    void closeSockets();
    void initSocket();
    bool loop();
    void receiveData(int client);

protected:
private:
    int _serverSocket;
    int _port;
    int _maxSocket;
    sockaddr_in _serverAddr{};
    std::vector<int> _clientSockets;
    fd_set _readfds;
};

#endif /* !SERVER_HPP_ */
