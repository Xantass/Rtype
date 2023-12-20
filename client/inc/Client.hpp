/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** Client
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <iostream>
#if defined(_WIN32)         
	#define CloseWindow RaylibCloseWindow
    #define ShowCursor RaylibShowCursor
    #undef CloseWindow
    #undef ShowCursor           // All USER defines and routines
#endif
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

        void initWindow(int width, int height, std::string title);
        bool shouldCloseWindow(void);
        void destroyWindow(void);

    protected:
    private:
        std::string _ip; ///< The server's ip
        std::string _port; ///< The server's port
        int _screenWidth;
        int _screenHeight;
};

#endif /* !CLIENT_HPP_ */
