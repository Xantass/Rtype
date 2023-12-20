/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** RoomManager
*/

#include "RoomManager.hpp"

RoomManager::RoomManager(int port)
{
    _port = port;
    _serverSocket = -1;
    _start = false;
}

RoomManager::~RoomManager()
{
}

int RoomManager::createRoom()
{
    int roomSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (roomSocket == -1) {
        std::cerr << "Erreur lors de la création du socket de la salle." << std::endl;
        return -1;
    }

    _serverAddr.sin_family = AF_INET;
    _serverAddr.sin_port = htons(_port);
    _serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(roomSocket, reinterpret_cast<struct sockaddr *>(&_serverAddr), sizeof(_serverAddr)) == -1) {
        std::cerr << "Erreur lors de la liaison du socket de la salle." << std::endl;
        close(roomSocket);
        return -1;
    }

    if (listen(roomSocket, 4) == -1) {
        std::cerr << "Erreur lors de l'attente de connexions pour la salle." << std::endl;
        close(roomSocket);
        return -1;
    }

    _serverSocket = roomSocket;
    FD_ZERO(&_readfds);
    FD_SET(_serverSocket, &_readfds);
    _maxSocket = _serverSocket;
    return roomSocket;
}

void RoomManager::initSocket()
{
    FD_ZERO(&_readfds);
    FD_SET(_serverSocket, &_readfds);

    for (const auto& roomSocket : _roomSockets) {
        FD_SET(roomSocket, &_readfds);
        if (roomSocket > _maxSocket) {
            _maxSocket = roomSocket;
        }
    }
}

void RoomManager::closeSockets()
{
    close(_serverSocket);
    for (const auto& clientSocket : _roomSockets) {
        close(clientSocket);
    }
    _roomSockets.clear();
}

void RoomManager::receiveData(int clientSocket)
{
    std::unique_ptr<char[]> buffer(new char[1024]);
    int bytesRead = recv(clientSocket, buffer.get(), 1024, 0);
    if (bytesRead <= 0) {
        if (bytesRead == 0) {
            std::cout << "Client déconnecté de la room" << std::endl;
        } else {
            std::cerr << "Erreur lors de la lecture des données du client." << std::endl;
        }
        close(clientSocket);
        for (auto it = _roomSockets.begin(); it != _roomSockets.end(); ++it) {
            if (*it == static_cast<int>(clientSocket)) {
                _roomSockets.erase(it);
                break;
            }
        }
    } else {
        buffer[bytesRead] = '\0';
        std::cout << "Message reçu du client : " << buffer.get() << std::endl;
        std::string str(buffer.get());
    }
    return;
}

void RoomManager::handleRooms() {
    timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 10000; // 10 ms

    while (true) {
        initSocket();
        int activity = select(_maxSocket + 1, &_readfds, nullptr, nullptr, &timeout);
        if ((activity < 0) && (errno != EINTR)) {
            std::cerr << "Erreur dans select pour les salles." << std::endl;
            break;
        }
        if (FD_ISSET(_serverSocket, &_readfds)) {
            std::cout << "CLIENT CONNECT INTO ROOM" << std::endl;
            int newSocket = accept(_serverSocket, nullptr, nullptr);
            _roomSockets.push_back(newSocket);
            _start = true;
        }
        for (auto& clientSocket : _roomSockets) {
            if (FD_ISSET(clientSocket, &_readfds)) {
                receiveData(clientSocket);
            }
        }
        if (_roomSockets.empty() && _start == true)
            break;
    }
    std::cout << "ROOM DELETE" << std::endl;
    closeSockets();
}