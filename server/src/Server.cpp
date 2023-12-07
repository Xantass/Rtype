/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** ServerMain
*/

#include "Server.hpp"

volatile sig_atomic_t signalReceived = 0;

void signalHandler(int signal) {
    if (signal == SIGINT || signal == SIGTERM) {
        signalReceived = 1;
    }
}

Server::Server(size_t port)
{
    _port = port;
    _serverSocket = -1;
}

Server::~Server()
{
}

bool Server::start()
{
    _serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (_serverSocket == -1) {
        std::cerr << "Erreur lors de la création du socket." << std::endl;
        return false;
    }

    _serverAddr.sin_family = AF_INET;
    _serverAddr.sin_addr.s_addr = INADDR_ANY;
    _serverAddr.sin_port = htons(_port);

    if (bind(_serverSocket, reinterpret_cast<struct sockaddr *>(&_serverAddr), sizeof(_serverAddr)) == -1) {
        std::cerr << "Erreur lors de la liaison du socket." << std::endl;
        close(_serverSocket);
        return false;
    }

    if (listen(_serverSocket, 5) == -1) {
        std::cerr << "Erreur lors de l'attente de connexions." << std::endl;
        close(_serverSocket);
        return false;
    }

    FD_ZERO(&_readfds);
    FD_SET(_serverSocket, &_readfds);
    _maxSocket = _serverSocket;

    return true;
}

void Server::closeSockets()
{
    close(_serverSocket);
    for (const auto& clientSocket : _clientSockets) {
        close(clientSocket);
    }
    _clientSockets.clear();
}

void Server::initSocket()
{
    FD_ZERO(&_readfds);
    FD_SET(_serverSocket, &_readfds);

    for (const auto& clientSocket : _clientSockets) {
        FD_SET(clientSocket, &_readfds);
        if (clientSocket > _maxSocket) {
            _maxSocket = clientSocket;
        }
    }
}

void Server::receiveData(int clientSocket)
{
    std::unique_ptr<char[]> buffer(new char[1024]);
    int bytesRead = recv(clientSocket, buffer.get(), 1024, 0);
    if (bytesRead <= 0) {
        if (bytesRead == 0) {
            std::cout << "Client déconnecté." << std::endl;
        } else {
            std::cerr << "Erreur lors de la lecture des données du client." << std::endl;
        }
        close(clientSocket);
        _clientSockets.erase(std::find(_clientSockets.begin(), _clientSockets.end(), static_cast<int>(clientSocket)), _clientSockets.end());
    } else {
        buffer[bytesRead] = '\0'; // Ajouter un caractère de fin de chaîne
        std::cout << "Message reçu du client : " << buffer.get() << std::endl;
    }
    return;
}

bool Server::loop()
{
    std::signal(SIGINT, signalHandler);
    std::signal(SIGTERM, signalHandler);
    timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 10000; // 10 ms

    while (!signalReceived) {
        initSocket();
        int activity = select(_maxSocket + 1, &_readfds, nullptr, nullptr, &timeout);
        if ((activity < 0)) {
            closeSockets();
            return false;
        }
        if (FD_ISSET(_serverSocket, &_readfds)) {
            int newSocket = accept(_serverSocket, nullptr, nullptr);
            _clientSockets.push_back(newSocket);
        }
        for (auto& clientSocket : _clientSockets) {
            if (FD_ISSET(clientSocket, &_readfds)) {
                receiveData(clientSocket);
            }
        }
    }

    return true;
}