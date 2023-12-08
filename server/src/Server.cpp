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

int Server::portAvailable(int port)
{
    int testSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (testSocket == -1) {
        std::cerr << "Erreur lors de la création du socket." << std::endl;
        return -1;
    }

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    for (int i = port; i > 0; ++i) {
        addr.sin_port = htons(i);
        if (bind(testSocket, reinterpret_cast<struct sockaddr *>(&addr), sizeof(addr)) != -1) {
            close(testSocket);
            return i; 
        }
    }
    close(testSocket);
    return -1;
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

int createRoom(int port) {
    RoomManager room(port);

    room.createRoom();
    room.handleRooms();
    return 0;
}

void Server::checkThreads()
{
    for (auto& thread : _threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}

void Server::checkCmd(std::string buffer, int clientSocket)
{
    int port = -1;

    if (buffer == "CREATE") {
        port = portAvailable(5000);
        if (port == -1)
            return;
        std::cout << "CREATE ROOM WITH PORT " + std::to_string(port) << std::endl;
        _threads.push_back(std::thread(createRoom, port));
        send(clientSocket, std::to_string(port).c_str(), std::to_string(port).length(), 0);
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
        for (auto it = _clientSockets.begin(); it != _clientSockets.end(); ++it) {
            if (*it == static_cast<int>(clientSocket)) {
                _clientSockets.erase(it);
                break;
            }
        }
    } else {
        buffer[bytesRead] = '\0';
        std::cout << "Message reçu du client : " << buffer.get() << std::endl;
        std::string str(buffer.get());
        checkCmd(str, clientSocket);
    }
    return;
}

void Server::closeThreads()
{
    for (auto& thread : _threads) {
        if (thread.joinable()) {
            thread.join(); // Attendre la fin de l'exécution du thread
        }
    }
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
        checkThreads();
        int activity = select(_maxSocket + 1, &_readfds, nullptr, nullptr, &timeout);
        if ((activity < 0)) {
            closeSockets();
            break;
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
    std::cout << "FREE MEMORY" << std::endl;
    closeSockets();
    closeThreads();
    return true;
}