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

std::string Client::getUsername() const
{
    return _username;
}

int Client::getID() const
{
    return _ID;
}

udp::endpoint Client::getClientEndpoint() const
{
    return _clientEndpoint;
}

bool Client::getAlive() const
{
    return _alive;
}

std::map<int, std::vector<unsigned char>> Client::getPacketsSend() const
{
    return _packetsSend;
}

std::map<int, std::vector<int>> Client::getPacketsReceive() const
{
    return _packetsReceive;
}

void Client::setUsername(const std::string& username)
{
    _username = username;
}

void Client::setID(int id)
{
    _ID = id;
}

void Client::setClientEndpoint(const udp::endpoint& clientEndpoint)
{
    _clientEndpoint = clientEndpoint;
}

void Client::setAlive(const bool& alive)
{
    _alive = alive;
}

void Client::addPacketSend(int timeStamp, std::vector<unsigned char> packet)
{
    _packetsSend[timeStamp] = packet;
}

void Client::delPacketSend(int timeStamp)
{
    _packetsSend.erase(timeStamp);
}

void Client::addPacketReceive(int timeStamp, std::vector<int> packet)
{
    _packetsReceive[timeStamp] = packet;
}

void Client::delPacketReceive(int timeStamp)
{
    _packetsReceive.erase(timeStamp);
}