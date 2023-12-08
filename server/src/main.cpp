/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** main
*/

#include "main.hpp"

int main(int argc, char **argv)
{
    Server server(12345);

    if (!server.start()) {
        return -1;
    }

    server.loop();

    server.closeSockets();

    return 0;
}