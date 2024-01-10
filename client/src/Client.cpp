/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** Client
*/

#if defined(_WIN32)         
	#define CloseWindow RaylibCloseWindow
    #define ShowCursor RaylibShowCursor
    #undef CloseWindow
    #undef ShowCursor           // All USER defines and routines
#endif
#include "../inc/Client.hpp"

Client::Client(std::string ip, std::string port) : _ip(ip), _port(port)
{
}

Client::~Client()
{
}
