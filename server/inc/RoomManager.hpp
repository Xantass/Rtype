/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** RoomManager
*/

#ifndef ROOMMANAGER_HPP_
#define ROOMMANAGER_HPP_

#ifdef _WIN32
    #include <winsock2.h>
#else
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <sys/select.h>
#endif

#include <iostream>
#include <vector>

class RoomManager {
public:
    /**
     * @brief Construct a new RoomManager object
     * 
     * @param port The port number to bind the RoomManager to
     */
    RoomManager(int port);

    /**
     * @brief Destroy the RoomManager object
     * 
     */
    ~RoomManager();

    /**
     * @brief Creates a new room
     * 
     * @return The ID of the created room
     */
    int createRoom();

    /**
     * @brief Initializes the socket for the RoomManager
     * 
     */
    void initSocket();

    /**
     * @brief Handles the rooms and their interactions
     * 
     */
    void handleRooms();

    /**
     * @brief Closes all client sockets
     * 
     */
    void closeSockets();

    /**
     * @brief Receives data from a specific client socket
     * 
     * @param clientSocket The socket associated with the client
     */
    void receiveData(int clientSocket);

protected:
private:
    int _serverSocket; /**< The RoomManager's socket file descriptor */
    int _port; /**< The port number the RoomManager is listening on */
    sockaddr_in _serverAddr; /**< RoomManager's server address information */
    std::vector<int> _roomSockets; /**< Vector to store room sockets */
    fd_set _readfds; /**< File descriptor set for select() */
    int _maxSocket; /**< The maximum number of sockets */
    bool _start; /**< Indicates if the RoomManager has started */
};


#endif /* !ROOMMANAGER_HPP_ */
