/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Client
*/

#include "Client.hpp"

Client::Client(std::string username, udp::endpoint clientEndpoint, int id)
{
    _username = username;
    _clientEndpoint = clientEndpoint;
    std::hash<std::string> hasher;
    _ID = id;
    _alive = true;
}

Client::Client(const Client& client)
{
    _username = client._username;
    _clientEndpoint = client._clientEndpoint;
    _ID = client._ID;
    _alive = client._alive;
}

Client::~Client()
{
}

std::string Client::getUsername() const {
    return _username;
}

int Client::getID() const {
    return _ID;
}

udp::endpoint Client::getClientEndpoint() const {
    return _clientEndpoint;
}

bool Client::getAlive() const {
    return _alive;
}

void Client::setUsername(const std::string& username) {
    _username = username;
}

void Client::setID(int id) {
    _ID = id;
}

void Client::setClientEndpoint(const udp::endpoint& clientEndpoint) {
    _clientEndpoint = clientEndpoint;
}

void Client::setAlive(const bool& alive)
{
    _alive = alive;
}