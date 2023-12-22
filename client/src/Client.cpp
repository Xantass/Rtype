/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** Client
*/

#include "../inc/Client.hpp"

Client::Client(std::string ip, std::string port) : _ip(ip), _port(port)
{
}

Client::~Client()
{
}

void Client::initWindow(int width, int height, std::string title)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(width, height, title.c_str());
    _screenWidth = width;
    _screenHeight = height;
}

bool Client::shouldCloseWindow(void)
{
    return WindowShouldClose();
}

void Client::destroyWindow(void)
{
    CloseWindow();
}
