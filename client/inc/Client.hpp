/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** Client
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <iostream>
#include "raylib.h"

/**
 * @class Client
 * @brief Class handling the graphic and connecting to server
 *
 */
class Client {
    public:
        /**
         * @brief Construct a new Client object
         *
         * @param ip The ip to connect to
         * @param port The port number to connect to
         */
        Client(std::string ip, std::string port);
        /**
         * @brief Destroy the Client object
         *
         */
        ~Client();

    protected:
    private:
        std::string _ip; ///< The server's ip
        std::string _port; ///< The server's port
};

#endif /* !CLIENT_HPP_ */
